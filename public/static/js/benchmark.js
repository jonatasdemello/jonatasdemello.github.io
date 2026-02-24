// Benchmarking

// Delete all Marks
performance.clearMarks();
// start Benchmarking
performance.mark("startFoo");

// .. do_something();

// stop Benchmarking
performance.mark("endFoo");
// create a measure
performance.measure("durationFoo", "startFoo", "endFoo");
// Delete the Measure "durationFoo"
performance.clearMeasures("durationFoo");


//returns us a list of all the marks that have been hit in our web application
var items = window.performance.getEntriesByType('mark');
//returns us a list of all the measures we’ve made.
var items = window.performance.getEntriesByType('measure');
// You can also get back a list of entries by using the specific name you’ve given them.
// return us a list with one item in it containing the ‘mark_fully_loaded’ time stamp in the startTime property
var items = window.performance.getEntriesByName('mark_fully_loaded');

function showResults() {
	var items = window.performance.getEntriesByType('measure');
	for (var i = 0; i < items.length; i++) {
		var req = items[i];
		var txtmsg = '( ' + paramA + ', ' + paramB + ' ) - XHR ' + req.name.toString() + ' took ' + req.duration.toString() + 'ms';
		console.log(txtmsg);
	}
}
