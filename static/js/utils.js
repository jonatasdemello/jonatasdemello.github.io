var utils = {};

//var canvas = document.getElementById("drawingCanvas");
//var context = myCanvas.getContext("2d");

function clearCanvas(canvas, myContext) {
	myContext.clearRect(0, 0, canvas.width, canvas.height);
	myContext.beginPath();
	myContext.stroke();
}

function drawAxes(canvas, myContext) {
	myContext.font = "10px Arial";
	myContext.fillStyle = "white";
	// myContext.fillStyle = "rgb(0,0,0)";

	// X-axis
	for (var x = 0; x < canvas.width; x += 50) {
		myContext.fillText(x, x, 10);
	}
	// Y-axis
	for (var y = 0; y < canvas.height; y += 50) {
		myContext.fillText(y, 0, y);
	}
}

function plot(x, y, myContext) {
	myContext.fillStyle = "rgb(" + x + "," + y + ",40)";
	myContext.fillRect(x * 2, (200 - y) * 2, 1, 1);
}

function plot(x, y) {
	myContext.fillStyle = "rgb(" + x + "," + y + ",40)";
	myContext.fillRect(x * 2, (200 - y) * 2, 1, 1);
}

function getRandomColor() {
	var letters = '0123456789ABCDEF';
	var color = '#';
	for (var i = 0; i < 6; i++) {
		color += letters[Math.floor(Math.random() * 16)];
	}
	return color;
}

function RND(start, end) {
	return Math.floor((Math.random() * end) + start);
}

// from green to red
//var colorMap= ["#060", "#090", "#0C0", "#0F0", "#9F0", "#9C0", "#990", "#960", "#930", "#900", "#C00"];

// Create an array of 10 colors
const colors = ["red", "blue", "green", "yellow", "purple", "orange", "pink", "brown", "black", "white"];

// Function to randomly select a color
function getRandomColorArray(arr) {
	const randomIndex = Math.floor(Math.random() * arr.length);
	return arr[randomIndex];
}

// Define your custom category: from green to red
let categories = ["#060", "#090", "#0C0", "#0F0", "#9F0", "#9C0", "#990", "#960", "#930", "#900", "#C00"];

// Calculate the interval width based on the number of categories
let intervalWidth = 0.99999999 / categories.length;

// Define the category boundaries
let boundaries = Array.from({ length: categories.length + 1 }, (_, i) => i * intervalWidth);

// Function to categorize the numbers
function categorize(number, boundaries, categories) {
	for (let i = 0; i < boundaries.length - 1; i++) {
		if (number >= boundaries[i] && number < boundaries[i + 1]) {
			return categories[i];
		}
	}
	return categories[categories.length - 1];
}

// Function to rank a number from 0 to 0.99999 intp categories
function rankColors(num) {
	return categorize(num, boundaries, categories);
}

