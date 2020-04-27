let stack = [];
let convert = [];
let temp = "";

let f = "(5*2)+(200+25)/2";
f = f.replace(/(\s*)/g,"");

function prec(op) {
    switch(op) {
        case '(' :
        case ')' :
            return 0;
        case '+' :
        case '-' :
            return 1;
        case '*' :
        case '/' :
            return 2;
    }
    return 999;
}

for(let i=0; i<f.length; i++) {

    const char = f.charAt(i);

    switch(char) {
        case '(' :
            stack.push(char);
            break;
        case '+' : case '-' : case '*' : case '/' :
            while(stack[stack.length-1]!=null &&
                 (prec(char) <= prec(stack[stack.length-1]))) {
                temp+=stack.pop();

                if(isNaN(stack[stack.length-1])) {
                    convert.push(temp);
                    temp = ""                    
                }
            }
            stack.push(char);
            break;
        case ')' :
            let returned_op = stack.pop();
            while(returned_op != '(') {
                temp+=returned_op;
                returned_op = stack.pop();

                if(isNaN(stack[stack.length-1])) {
                    convert.push(temp);
                    temp = ""                    
                }
            }
            break;
        default : 
            temp+=char;
            if(isNaN(f.charAt(i+1)) || (i+1 == f.length) ) {
                convert.push(temp);
                temp = ""
            }
            break; 
    }
}

while(stack.length != 0) {
    convert.push(stack.pop());
}

for(let i in convert) {
    if(!isNaN(convert[i])) {
        stack.push(convert[i]);
    }
    else {
        const b = parseFloat(stack.pop());
        const a = parseFloat(stack.pop());
        switch(convert[i]) {
            case '+':
                stack.push(a+b);
                break;
            case '-':
                stack.push(a-b);
                break;
            case '*':
                stack.push(a*b);
                break;
            case '/':
                stack.push(a/b);
                break;
        }
    }
}

let result = "";
for(let i in convert) {
    result+=convert[i];
    result+=" "; 
}
console.log(f);
console.log(result)
console.log("Result = " + stack);