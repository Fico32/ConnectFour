#include <iostream>
#include <string>
#include "slot.h"
#include "row.h"
#include "gameboard.h"
#include "./uWebSockets/src/App.h"

using namespace std;

int main()
{
	struct PerSocketData {
        /* Define your user data */
        int something;
    };
	
	int rows = 6;
	int cols = 7;
	int tempRows = 0;
	int tempCols = 0;
	//cout << "Type in the number of rows and the number of columns you want the board to have: ";
	//cin >> tempRows;
	//cin >> tempCols;
	if(tempRows != 0)
	{
		cols = tempCols;
		rows = tempRows;
	}
		
	Gameboard * board = new Gameboard(6,7);
	
	uWS::SSLApp({
	  .key_file_name = "misc/key.pem",
	  .cert_file_name = "misc/cert.pem",
	  .passphrase = "1234"
	}).ws<PerSocketData>("/*", {
        /* Settings */
        .compression = uWS::SHARED_COMPRESSOR,
        .maxPayloadLength = 16 * 1024,
        .idleTimeout = 12,
        .maxBackpressure = 1 * 1024 * 1024,
        /* Handlers */
        .upgrade = [board, rows, cols](auto *res, auto *req, auto *context) mutable{
						cout << "upgrade" << endl;
            res->template upgrade<PerSocketData>({
                /* We initialize PerSocketData struct here */
                 .something = 13
            }, req->getHeader("sec-websocket-key"),
                req->getHeader("sec-websocket-protocol"),
                req->getHeader("sec-websocket-extensions"),
                context); 
			board->refresh(6,7);
        },
        .open = [](auto *ws) {
            /* Open event here, you may access ws->getUserData() which points to a PerSocketData struct.
             * Here we simply validate that indeed, something == 13 as set in upgrade handler. */
            //std::cout << "Something is: " << static_cast<PerSocketData *>(ws->getUserData())->something << std::endl;
			cout << "open" << endl;
        },
        .message = [board] (auto *ws, std::string_view message, uWS::OpCode opCode) mutable {
			int gameOver = 0;
			int row = 0;
			if(message != "Nan"){
				row = stoi(string{message});
			}
			else{
				return;
			}
			int lastSpot = board->makeMove(row);
			gameOver = board->isGameOver(row,lastSpot);
			
			cout << gameOver << endl;
			string coords = to_string(row) + " ";
			coords = coords + to_string(lastSpot);
			coords = coords + " " + to_string(board->getCurPlayer());
			coords = coords + " " + to_string(gameOver);
			
			cout << "message" << endl;
			cout << coords << endl;
            ws->send(coords, opCode);
        },
        .drain = [](auto */*ws*/) {
            /* Check ws->getBufferedAmount() here */
        },
        .ping = [](auto */*ws*/, std::string_view) {
            /* You don't need to handle this one, we automatically respond to pings as per standard */
        },
        .pong = [](auto */*ws*/, std::string_view) {
            /* You don't need to handle this one either */
        },
        .close = [](auto */*ws*/, int /*code*/, std::string_view /*message*/) {
            /* You may access ws->getUserData() here, but sending or
             * doing any kind of I/O with the socket is not valid. */
			 			cout << "close" << endl;
        }
    }).listen(3000, [](auto *listen_socket) {
	    if (listen_socket) {
			std::cout << "Listening on port " << 3000 << std::endl;
	    }
	}).run();
	
	delete board;
}
