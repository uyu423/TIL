class Developer {
  fullName: string;
  constructor(public firstName: string, public lastName: string) {
    this.fullName = `${firstName} ${lastName}`;
  }
}

interface Person {
  firstName: string,
  lastName: string,
}

function hello(person: Person) {
  return `Hello, ${person.firstName} ${person.lastName}`;
}

// const user = "Yowu";
const data = {
  firstName: "Yowu",
  lastName: "Yu",
}

const user = new Developer(data.firstName, data.lastName);

console.log(user);
console.log(hello(user));
