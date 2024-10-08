
function* inorderTraversal(arg) {
    if (!Array.isArray(arg)) {
        yield arg;
        return;
    }
    for (let element of arg) {
        yield* inorderTraversal(element);
    }
}

const input = [[[6]],[1,3],[]];

for (let int of inorderTraversal(input)) {
  console.log(int);
}
