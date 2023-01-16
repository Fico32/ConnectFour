let isGameOver = false;
let rows = 6;
let cols = 7;
let circles;
let reOrganizedCircles = [];
let color = 'yellow';

//Sets up websocket
const exampleSocket = new WebSocket('ws://localhost:3000');
document.querySelector('.clickable').addEventListener('click', async function (event) {
    let rowNum = parseInt($(event.target).closest('.grid-item')[0]?.classList[1]);
    let x = await exampleSocket.send(rowNum);
});
exampleSocket.onmessage = (event) => {
    let message = event.data.split(' ');
    let coords = [message[0], message[1]];
    let playerNmber = parseInt(message[2]);
    let isGameOver = parseInt(message[3]);
    coords = coords.map(elem => parseInt(elem) );
    color = playerNmber == 1 ? 'yellow' : 'red';
    d3.select(reOrganizedCircles[coords[0]][coords[1]]).style("fill", color);
    if (isGameOver) {
        gameOver();
    }
}

function makeGrid(rows, cols) {
    const grid = document.querySelector('.grid-container');
    grid.style.gridTemplateColumns = `repeat(${cols}, auto)`;
    let places = rows * cols;
    for (let i = 0; i < places; i++) {
        let container = document.createElement('div');
        let className = i % cols + 'row';
        container.classList.add('grid-item');
        container.classList.add(className);
        let width = container.offsetWidth;
        let height = container.offsetHeight;
        console.log(width)
        console.log(height)
        let svg = d3.select(container).append("svg").attr("width", 100).attr("height", 100);
        svg.append('circle')
            .attr('cx', 50)
            .attr('cy', 50)
            .attr('r', 25)
            .attr('stroke', 'black')
            .attr('fill', '#ffffff');
        grid.append(container);
    }
    circles = document.querySelectorAll('circle');
    for (let i = 0; i < cols; i++) {
        let temp = [];
        for (let j = 0; j < rows; j++) {
            temp.unshift(circles[i + cols * j]);
        }
        reOrganizedCircles.push(temp);
    }
}

function gameOver() {
    console.log("the game is over");
    document.querySelector('.gameOver').style.visibility = 'visible';
}

function restartGame() {
    makeGrid(rows, cols);
}

makeGrid(rows, cols);
