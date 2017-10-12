// 2 dimensions:

var arrayName = new Array(new Array());

// 4x4 example (actually 4x<anything>):

var matrix = [ [],[],[],[] ]

// which can filled by:

for (var i=0; i<4; i++) {
   for (var j=0; j<4; j++) {
      matrix[i][j] = i*j;
   }
}

Array.matrix = function(numrows, numcols, initial) {
    var arr = [];
    for (var i = 0; i < numrows; ++i) {
        var columns = [];
        for (var j = 0; j < numcols; ++j) {
            columns[j] = initial;
        }
        arr[i] = columns;
    }
    return arr;
}

//Here is some code to test the definition:
var nums = Array.matrix(5,5,0);
print(nums[1][1]); // displays 0
var names = Array.matrix(3,3,"");
names[1][2] = "Joe";
print(names[1][2]); // display "Joe"

//We can also create a two-dimensional array and initialize it to a set of values in one line:

var grades = [[89, 77, 78],[76, 82, 81],[91, 94, 89]];
print(grades[2][2]); // displays 89
