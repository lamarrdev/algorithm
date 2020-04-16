let stack = [];
let convert = [];
let temp = "";

let f = "(5*2)+ (200 + 25)/2";
f = f.replace(/(\s*)/g,"");

for(let i=0; i<f.length; i++) {
    if(!isNaN(f.charAt(i))) {
        temp+=f.charAt(i);
        if(isNaN(f.charAt(i+1)) || (i+1 == f.length) ) {
            convert.push(temp);
            temp = ""
        }
    }
    else if(f.charAt(i) == "(") {
        stack.push("(");
    }
    else if(f.charAt(i) == ")") {
        while(stack.length) {
            if(stack[stack.length - 1] == '(') {
                stack.pop();
                break;
            }
            convert.push(stack.pop());
        }

    }
    else if(f.charAt(i) == "*" || f.charAt(i) == "/") {
        stack.push(f.charAt(i));
    }
    else if(f.charAt(i) == "+" || f.charAt(i) == "-") {
        while(stack.length) {
            if(stack[stack.length - 1] == '(') {
                break;
            }
            convert.push(stack.pop());
        }
        stack.push(f.charAt(i));
    }
}

while(stack.length) {
    convert.push(stack.pop());
};

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