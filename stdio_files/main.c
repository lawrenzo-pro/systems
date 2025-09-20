#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
struct person{
    char *name;
    uint8_t age;
};
struct employee{
    struct person *person;
    uint16_t employee_id;
};
struct employee_node{
    struct employee employee;
    struct employee_node *next;
};
typedef struct person* Person;
typedef struct employee Employee;
typedef struct employee_node* Node;
void print_employee_details(Employee employee){
    printf("Name:%s\nAge:%d\nId:%d\n",employee.person->name,employee.person->age,employee.employee_id);
}
Person new_person(char *name, uint8_t age){
    Person person = malloc(sizeof(Person));
    person->age = age;
    person->name = malloc(50); //I assume 50bytes can store any name.
    strcpy(person->name,name);
    return person;
}
Employee new_employee(Person person){
    static uint16_t curr_id = 0;
    Employee employee;
    employee.employee_id = curr_id;
    curr_id++;
    employee.person = person;
    return employee;
}
Node new_node(Employee employee){
    Node node = malloc(sizeof(Node));
    node->employee = employee;
    node->next = NULL;
    return node;
}
void add_employee_to_list(Node head, Employee employee){
    Node current = head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = new_node(employee);
}
Employee get_employee_by_id(Node head,uint16_t id){
    Node current = head;
    while(current != NULL){
        if(current->employee.employee_id == id){
            return current->employee;
        }
        current = current->next;
    }
    return current->employee; // This will byte us later but anyway....
}
void save_employee_list(Node head,char *filename){
    FILE *employee_file = fopen(filename,"wb");
    Node current = head;
    while(current != NULL){
        fwrite(&(current->employee),sizeof(struct employee), 1, employee_file);
        //print_employee_details(current->employee);
        current = current->next;
    }
    fclose(employee_file);
}

Node read_employee_list(char *filename){
    FILE *employee_file = fopen(filename, "rb");
    Node head = NULL;
    Node tail = NULL;
    Employee temp_employee;

     while (fread(&temp_employee, sizeof(Employee), 1, employee_file) == 1) {
        // Create a new node for each employee read
        Node new_node = malloc(sizeof(Node));
        if (!new_node) {
            perror("Error allocating memory");
            break; 
        }
        new_node->employee = temp_employee;
        new_node->next = NULL;
        if(head == NULL){
            head = new_node;
        }
        else{
            add_employee_to_list(head,temp_employee);
        }
    }

    fclose(employee_file);
    return head;
}

int main(){
    Person person1 = new_person("Lawrence Kimani", 21);
    Person person2 = new_person("John Doe", 22);
    Person person3 = new_person("Jane Doe", 24);
    Person person4 = new_person("Michelle Parker",21);

    Employee employee1 = new_employee(person4);
    Employee employee2 = new_employee(person1);
    Employee employee3 = new_employee(person3);
    Employee employee4 = new_employee(person2);

    Node employee_list = new_node(employee4);
    add_employee_to_list(employee_list, employee3);
    add_employee_to_list(employee_list,employee2);
    add_employee_to_list(employee_list,employee1);

    Employee got_employee = get_employee_by_id(employee_list,0);
    print_employee_details(got_employee);
    save_employee_list(employee_list,"employees.bin");

    //There is some weird behaviour here (It segfaults)
   Node got_from_file = read_employee_list("employees.bin");
   print_employee_details(get_employee_by_id(got_from_file,3));
    return 0;
}