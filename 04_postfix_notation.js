const Node = function(str) {
    this.data = str;
    this.prev = null;
    this.next = null;
}

const LinkedListStack = function() {
    this.top = null;
    this.size = 0;
}

LinkedListStack.prototype.push = function(str) {
    const newNode = new Node(str);

    if(this.top != null) {
        const oldTop = this.top;
        oldTop.next = newNode;
        newNode.prev = oldTop;
    } 
    this.top = newNode;
    this.size++;
}

LinkedListStack.prototype.pop = function() {
    const oldTop = this.top;
    this.top = this.top.prev;
    this.size--;
    return oldTop.data;
}

const stack = new LinkedListStack();

let f = "1 + 2 * 3";
let result = "";
// 문자열의 모든 공백 제거
f = f.replace(/(\s*)/g,"");

for(let i=0; i<f.length; i++) {
    // 숫자가 나오면 그대로 결과에 넣는다.
    if(!isNaN(f.charAt(i))) {
        result = result + f.charAt(i);
    }
    // "("가 나오면 stack에 푸쉬한다
    else if(f.charAt(i) == "(") {
        stack.push("(");
    }
    // ")"가 나오면 "(" 까지의 노드를 하나씩 결과에 넣는다.
    else if(f.charAt(i) == ")") {
        while(stack.top != null) {
            // 현재의 top이 ( 이면, 스택에서 ( 삭제해주고 반복문 종료
            if(stack.top.data == '(') {
                stack.pop();
                break;
            }
            result = result + stack.pop();
        }
    }
    // * / 가 나오면 스택에 push 한다.
    else if(f.charAt(i) == "*" || f.charAt(i) == "/") {
        stack.push(f.charAt(i));
    }
    // + - 가 나오면 스택에 푸쉬한다.
    // 만약 스택의 비어있지 않은 경우 스택의 끝까지 결과에 넣어준다.
    // 만약 ( 가 있는 경우  ( 가 나올때까지 출력하고 pop한다.
    else if(f.charAt(i) == "+" || f.charAt(i) == "-") {
        while(stack.top != null) {
            if(stack.top.data == '(') {
                break;
            }
            result = result + stack.pop();
        }
        stack.push(f.charAt(i));
    }
}

while(stack.top != null) {
    result = result + stack.pop();
}

console.log(result);


// console.log(f.length);
// console.log(f.charAt(0));
// console.log(!isNaN(f.charAt(0)));

