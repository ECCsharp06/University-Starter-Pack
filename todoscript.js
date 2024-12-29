const inputElement = document.querySelector("#todo-input");
const todoListElement = document.querySelector(".todos");
const addBtnElement = document.getElementById("add-btn");

addBtnElement.addEventListener("click", addTodo);
function addTodo(cheese) {
  cheese.preventDefault();
  const newMisson = inputElement.value;
  if (newMisson.trim() == "") {
    alert("BOŞ TO-DO EKLENEMEZ!");
  } else {
    const todo_div = document.createElement("div");
    todo_div.classList.add("todo");
    todoListElement.appendChild(todo_div);
    const check_icon = document.createElement("i");
    check_icon.classList.add("fa-solid", "fa-check", "check");
    todo_div.appendChild(check_icon);
    const todo_content = document.createElement("input");
    todo_content.classList.add("todo-content");
    todo_content.type = "text";
    todo_content.value = newMisson;

    todo_content.readOnly = true;
    todo_div.appendChild(todo_content);
    inputElement.value = "";

    const todo_icon = document.createElement("div");
    todo_icon.classList.add("todo-icon");
    todo_div.appendChild(todo_icon);

    const delete_icon = document.createElement("i");
    delete_icon.classList.add("fa-solid", "fa-trash", "delete");
    todo_icon.appendChild(delete_icon);

    const edit_icon = document.createElement("i");
    edit_icon.classList.add("fa-solid", "fa-pencil", "edit");
    todo_icon.appendChild(edit_icon);

    delete_icon.addEventListener("click", deleteTodo);
    check_icon.addEventListener("click", checkTodo);
    edit_icon.addEventListener("click", editTodo);
  }
}
function deleteTodo(lemonade) {
  const selectTodo = lemonade.target.parentElement.parentElement;
  selectTodo.remove();
}
function checkTodo(e) {
  const checkTodo = e.target.parentElement;
  const todoContentElement = checkTodo.querySelector(".todo-content");
  todoContentElement.classList.toggle("completed");
}
function editTodo(theevent) {
  const todoItem = theevent.target.parentElement.parentElement;
  const todoContentElement = todoItem.querySelector(".todo-content");
  todoContentElement.removeAttribute("readonly");
  todoContentElement.focus();
  todoContentElement.style.color = "#687280";
  todoContentElement.addEventListener("keyup", (theevent) => {
    if (theevent.key === "Enter") {
      todoContentElement.readOnly = true;
      todoContentElement.style.color = "white";
    }
  });
}
