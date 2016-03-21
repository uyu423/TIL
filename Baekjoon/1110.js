//try 1 failed : 90% Timeout
//try 2 failed : 90% invaild answer
//try 3 failed : Compiler Error (can't use 'return' macro out of function)
//try 4 success : input '0' checking
//note : input 0일 때를 고려해서 알고리즘을 짰어야됨. 그걸 놓쳐서 0일때만 예외처리함.. (line 11)

function main() {
	var origin = parseInt(require('fs').readFileSync('/dev/stdin').toString());
	var prev = origin + '';
	if(origin < 10) prev = '0' + prev;
	if(origin == 0) { console.log('1'); return; }
	var arr = []; var newNum = ''; var sum = 0;
	for(var cnt = 0; origin != parseInt(sum); cnt++) {
		newNum = '' + (parseInt(prev[0]) + parseInt(prev[1]));
		if(newNum[1] == undefined) { newNum = '0' + newNum; }
		sum = prev[1] + newNum[1];
		prev = sum;
	}
	console.log(cnt);
}

main();
