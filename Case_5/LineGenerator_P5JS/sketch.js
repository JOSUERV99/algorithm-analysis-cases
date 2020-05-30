let lines, amount, modes;

const WIDTH = 600,
      HEIGHT = 480;

// const WIDTH = 1920,
//       HEIGHT = 1080;

const VERTICAL = 0, 
      HORIZONTAL = 1, 
      DIAGONAL_FROM_TOP = 2,
      DIAGONAL_FROM_LEFT = 3;

function setup() {
  
  modes = 4;
  amount = 10;
  lines = [];
  
  loadLines();
  
  createCanvas(WIDTH, HEIGHT);
}

function draw() {
  background(220);
  
  for (let i=0; i<amount; 
       drawLine( lines[i] ) , 
  i++);
  
}

function loadLines() {
  
  lines = [];
  
  for (let i=0; i<amount; i++)
    lines.push( createLine() );
}

function createLine() {
  let line = [];
  let m = int(random(modes));
  
  let rX = int( random(WIDTH) );
  let rY = int( random(HEIGHT) );
  
  // to choose the side for diagonals
  let coin = int(random(2)) == 1;
  
  switch(m) {
  
    case HORIZONTAL:
      line.push( [0, rY] );
      line.push( [WIDTH, rY] );
    break;
    case VERTICAL:
      line.push( [rX, 0]);
      line.push( [rX, HEIGHT] );
    break;
    case DIAGONAL_FROM_TOP:
      
      line.push( [rX, 0] );
      if (coin) 
        line.push( [WIDTH, rY] ); 
      else 
        line.push( [0, rY] ); 
           
    break;
    case DIAGONAL_FROM_LEFT:
  
      line.push( [0, rY] );
      if (coin) 
        line.push( [rX, HEIGHT] ); 
      else 
        line.push( [rX, 0] ); 
      
    break;
    default:
      console.log("?");
  }
  
  return line;
  
}

function saveFile() {
  saveJSON( {lines} , 'lines.json');
}

function drawLine(l) {
  line( l[0][0], l[0][1], l[1][0], l[1][1]);
}

