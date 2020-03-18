let radius, angle, divisions, scale;
let myPoints, myOtherPoints, w, h, offset;
let circles, movement1, movement2;

function setup() {
  w = 650;
  h = 500;
  createCanvas(w, h);
  radius = 20;
  angle = 0;
  divisions = 15;
  circles = 6;
  scale = 2 * PI / divisions;
  
  // create points
  myPoints = getPoints(divisions, scale);
  myOtherPoints = getPoints(divisions, scale);
}

function draw() {
  background(0);
  
  
  translate((w/2), (h/2));
  for (let offset = 0; offset< 100; offset+=25)
    for (let i=0; i<myPoints.length; i++)
      myPoints[i].show(offset, angle);
  
  
  translate(-20, -20);
  for (let offset = 0; offset< 100; offset+=25)
    for (let i=0; i<myOtherPoints.length; i++)
      myOtherPoints[i].show(offset, angle);
  
  angle += 0.01;
}

function getPoints(n, scale) {
  let points = [];
  for(let i=0; i<n*scale; i+=scale) {
    points.push(new MyPoint(cos(i), sin(i)));
  }
  return points;
}

function MyPoint(x, y) {
  this.x = x;
  this.y = y;
  this.show = function(offset, movement) {
    stroke(255);
    fill('blue');
    rect( x*(radius + offset)*cos(movement), 
         y*(radius + offset)*sin(movement), 
         2, 2);
  }
}