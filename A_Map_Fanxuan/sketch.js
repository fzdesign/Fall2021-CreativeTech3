//Followed along with Daniel Shiffman's tutorial https://www.youtube.com/watch?v=pdaNttb7Mr8'
let model;
let strokePath = null;

let x, y;
let pen = "down";

function setup() {
  createCanvas(windowWidth, windowHeight);
  x = windowWidth/2;
  y = windowWidth/4;
  model = ml5.sketchRNN("map", modelReady);
  background(255);
}

function modelReady() {
  console.log("model ready");
  model.reset();
  model.generate(gotSketch);
}

function draw() {
  //translate(width / 2, height / 2);
  if (strokePath != null) {
    let newX = x + strokePath.dx;
    let newY = y + strokePath.dy;
    if (pen == "down") {
      stroke(0,10);
      strokeWeight(3);
      
      line(x, y, newX, newY);
    }
    pen = strokePath.pen;
    strokePath = null;
    x = newX;
    y = newY;

    if (pen !== "end") {
      model.generate(gotSketch);
    } else {
      console.log("drawing complete");
      model.reset();
      model.generate(gotSketch);
      x = windowWidth/2;
      y = windowWidth/4;
    }
  }
}

function gotSketch(error, s) {
  if (error) {
    console.error(error);
  } else {
    strokePath = s;
    //console.log(strokePath);
  }
}
