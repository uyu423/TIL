var Developer = /** @class */ (function () {
    function Developer(firstName, lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.fullName = firstName + " " + lastName;
    }
    return Developer;
}());
function hello(person) {
    return "Hello, " + person.firstName + " " + person.lastName;
}
// const user = "Yowu";
var data = {
    firstName: "Yowu",
    lastName: "Yu"
};
var user = new Developer(data.firstName, data.lastName);
console.log(user);
console.log(hello(user));
