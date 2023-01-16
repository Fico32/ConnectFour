# ConnectFour

The C++ code relies on the uWebSockets library which can be found here: https://github.com/uNetworking/uWebSockets.
Simply downloading the repo and putting it into a folder titled uWebSockets inside of the backend folder is enough to integrate it.
To run the program you can compile with the makefile and then run ./connect.
Then you must open the website by hosting the index.html on some localhost. This can be done using anything. One possible easy solution it to navigate to the correct directory and run the python command to host a server. Then once you navigate to the localhost you can play the game. Make sure that localhost:3000 is not in use as the websocket uses this. To play simply click on one of the columns on the board and it will place a piece. To restart the game you can simply reload the page.
