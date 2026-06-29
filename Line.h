#ifndef ASSIGNMENT_4_LINE_H
#define ASSIGNMENT_4_LINE_H

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

class Line {
public:
    virtual void print() const = 0;
    virtual std::string serialize() const = 0;
    virtual ~Line() {}
};

class TextLine : public Line {
private:
    std::string text;
public:
    TextLine(const std::string& t) : text(t) {}

    std::string serialize() const override {
        return "T:" + text;
    }

    void print() const override {
        std::cout << "Text: " << text << std::endl;
    }

    std::string getText() const {return text; }

    void setText(const std::string& newText) {text = newText; }
};

class CheckListLine : public Line {
private:
    std::string item;
    bool checked;
public:
    CheckListLine(const std::string& i, bool c) : item(i), checked(c) {}

    std::string serialize() const override {
        std::string status = checked ? "1" : "0";

        return "C:" + status + ":" + item;
    }

    void print() const override {
        std::cout << "[ " << (checked ? "x" : " ") << " ] " << item << std::endl;
    }

    std::string getItem() const {return item; }
    bool getChecked() const {return checked; }

    void setItem(const std::string& newItem) {item = newItem; }
    void setChecked(bool newChecked) {checked = newChecked; }
};

class ContactLine : public Line {
private:
    std::string firstName;
    std::string lastName;
    std::string email;
public:
    ContactLine(const std::string& f, const std::string& l, const std::string& e) : firstName(f), lastName(l), email(e) {}

    std::string serialize() const override {
        return "I:" + firstName + ":" + lastName + ":" + email;
    }

    void print() const override {
        std::cout << "Contact - " << firstName << " " << lastName << ", " << "E-mail: " << email << std::endl;
    }

    std::string getFirstName() const {return firstName; }
    std::string getLastName() const {return lastName; }
    std::string getEmail() const {return email; }

    void setFirstName(const std::string& newFirstName) {firstName = newFirstName; }
    void setLastName(const std::string& newLastName) {lastName = newLastName; }
    void setEmail(const std::string& newEmail) {email = newEmail; }
};

#endif //ASSIGNMENT_4_LINE_H
