#include <iostream>
#include <string>
#include <vector>
using namespace std;

class student
{
protected:
    static int count;
    string studentname;
    int rollnumber;
    char sec;
    string phonenumber;
    string emailid;

public:
    student() {}
    student(string name, char s, string phone, string email)
    {
        count++;
        studentname = name;
        rollnumber = count;
        sec = s;
        phonenumber = phone;
        emailid = email;
    }

    void studentdetails()
    {
        cout << "\n\n"
             << "Name: " << studentname << endl
             << "Roll Number: " << rollnumber << endl
             << "Section: " << sec << endl
             << "Phone Number: " << phonenumber << endl
             << "Email Id: " << emailid << endl;
    }
};
int student::count = 0;

class internals : virtual public student
{
protected:
    float imaths, iphysics, icpp, ienglish;

public:
    internals() {}
    internals(float iM, float iP, float iC, float iE, string in, char ise, string ip, string ie) : student(in, ise, ip, ie)
    {
        imaths = iM;
        iphysics = iP;
        icpp = iC;
        ienglish = iE;
    }

    internals(internals &&other) noexcept
        : student(std::move(other)), imaths(other.imaths), iphysics(other.iphysics), icpp(other.icpp), ienglish(other.ienglish) {}

    internals &operator=(internals &&other) noexcept
    {
        if (this != &other)
        {
            student::operator=(std::move(other));
            imaths = other.imaths;
            iphysics = other.iphysics;
            icpp = other.icpp;
            ienglish = other.ienglish;
        }
        return *this;
    }

    void idisplay()
    {
        cout << "\nInternal Marks:" << endl;
        cout << "Mathematics: " << imaths << endl;
        cout << "Physics: " << iphysics << endl;
        cout << "C++: " << icpp << endl;
        cout << "English: " << ienglish << endl;
    }
};

class externals : virtual public student
{
protected:
    float emaths, ephysics, ecpp, eenglish;

public:
    externals() {}
    externals(float eM, float eP, float eC, float eE, string en, char ese, string ep, string ee) : student(en, ese, ep, ee)
    {
        emaths = eM;
        ephysics = eP;
        ecpp = eC;
        eenglish = eE;
    }

    externals(externals &&other) noexcept
        : student(std::move(other)), emaths(other.emaths), ephysics(other.ephysics), ecpp(other.ecpp), eenglish(other.eenglish) {}

    externals &operator=(externals &&other) noexcept
    {
        if (this != &other)
        {
            student::operator=(std::move(other));
            emaths = other.emaths;
            ephysics = other.ephysics;
            ecpp = other.ecpp;
            eenglish = other.eenglish;
        }
        return *this;
    }

    void edisplay()
    {
        cout << "\nExternal Marks:" << endl;
        cout << "Mathematics: " << emaths << endl;
        cout << "Physics: " << ephysics << endl;
        cout << "C++: " << ecpp << endl;
        cout << "English: " << eenglish << endl;
    }
};

class total : public internals, public externals
{
protected:
    float tmaths, tphysics, tenglish, tcpp;

public:
    total(float &eM, float &eP, float &eC, float &eE, float &iM, float &iP, float &iC, float &iE, string n, char se, string p, string e) : internals(iM, iP, iC, iE, n, se, p, e), externals(eM, eP, eC, eE, n, se, p, e)
    {
        tmaths = eM + iM;
        tphysics = eP + iP;
        tcpp = eC + iC;
        tenglish = eE + iE;
    }
    void tdisplay()
    {
        cout << "Total marks of student name: " << studentname << endl
             << "Roll Number: " << rollnumber << endl
             << "Mathematics: " << tmaths << endl
             << "Physics: " << tphysics << endl
             << "C++: " << tcpp << endl
             << "English: " << tenglish << endl;
    }
};

class result : public total
{
protected:
    float res;

public:
    result(float iM, float iP, float iC, float iE, float eM, float eP, float eC, float eE, string n, char se, string p, string e) : total(eM, eP, eC, eE, iM, iP, iC, iE, n, se, p, e)
    {
        res = (tmaths + tphysics + tcpp + tenglish) / 4;
    }
    void rdisplay()
    {
        cout << "Result of student name: " << studentname << endl
             << "Roll Number: " << rollnumber << endl
             << "Grade: ";
        if (res >= 90)
            cout << "A+";
        else if (res >= 80 && res < 90)
            cout << "A";
        else if (res >= 70 && res < 80)
            cout << "B";
        else if (res >= 60 && res < 70)
            cout << "C";
        else
            cout << "Fail";
        cout << endl;
    }
};

int main()
{
    int size;
    cout << "Enter number of students: ";
    cin >> size;
    vector<result> students;
    string name, phone, email;
    float em, ep, ec, ee, im, ip, ic, ie;
    char sec;
    for (int i = 0; i < size; i++)
    {
        cout << "Enter the name of student no " << i + 1 << ": ";
        cin >> name;
        cout << "Enter the section: ";
        cin >> sec;
        cout << "Enter the phone number: ";
        cin >> phone;
        cout << "Enter the emailid: ";
        cin >> email;
        cout << "Enter the internal marks of student:" << endl;
        cout << "Mathematics: ";
        cin >> im;
        cout << "Physics: ";
        cin >> ip;
        cout << "C++: ";
        cin >> ic;
        cout << "English: ";
        cin >> ee;
        students.push_back(result(im, ip, ic, ie, em, ep, ec, ee, name, sec, phone, email));
        cout << "\n\n";
    }
    cout << "---- Students Results -----\n";
    for (int i = 0; i < size; i++)
    {
        students[i].rdisplay();
    }
    return 0;
}
