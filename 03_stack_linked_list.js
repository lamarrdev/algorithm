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
}

LinkedListStack.prototype.pop = function() {
    temp = this.top;
    this.top = this.top.prev;
    this.top.next = null;
    return temp;
}

const stack = new LinkedListStack();
console.log("Push a node");
stack.push("AAA");
console.log(stack.top.data+"\n");

console.log("Push three nodes");
stack.push("BBB");
stack.push("CCC");
stack.push("DDD");
console.log(stack.top.data+"\n");

console.log("Pop");
stack.pop();
console.log(stack.top.data+"\n");

console.log("Pop two times");
stack.pop();
stack.pop();
console.log(stack.top.data+"\n");