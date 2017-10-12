var utils = {};

function drawAxes(canvas, ctx)
{
	//var canvas = document.getElementById("drawingCanvas");
	//var context = canvas.getContext("2d");

    ctx.font = "10px Arial";
    ctx.fillStyle = "rgb(0,0,0)";
    // X-axis
    for (var i=0; i<canvas.width; i+=50)
    {
        ctx.fillText(i,i,10);
    }
    // Y-axis
    for (var i=0; i<canvas.height; i+=50)
    {
        ctx.fillText(i,0,i);
    }
}
