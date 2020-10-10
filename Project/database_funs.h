#ifndef DATABASEFUNS_H
#define DATABASEFUNS_H

#include <iostream>
#include <winsock.h> // necessary files needed to be add in include folder in mingw
#include <mysql.h>  
#include <windows.h>
#include <sstream>
#include <map>

using namespace std;

//function to add new record in databse
void addrecord(string acc_no, string PIN, string name, string balance, string mobile_number, string email, string status)
{
    MYSQL *conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "remotemysql.com", "mH2kQ9m8IW", "tXfgICQA3d", "mH2kQ9m8IW", 3306, NULL, 0);

    int qstate;
    stringstream ss;

    ss << "INSERT INTO ATM_users (acc_num , PIN , name , balance , Mobile_number , email , status ) VALUES('" << acc_no << "' , '" << PIN << "' , '" << name << "' , '" << balance << "' , '" << mobile_number << "' , '" << email << "' , '" << status << "')";
    string query = ss.str();
    const char *q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0)
        cout << "Record Inserted" << endl;
    else
        cout << "failed" << endl;

    mysql_close(conn);
}

//updates the user record when user logs out
void updaterecord(map<string, string> user)
{
    MYSQL *conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "remotemysql.com", "mH2kQ9m8IW", "tXfgICQA3d", "mH2kQ9m8IW", 3306, NULL, 0);
    int qstate;
    stringstream ss;
    ss << "UPDATE ATM_users SET PIN = " << user["PIN"] << " , balance = '" << user["balance"] << "' , email = '" << user["email"] << "' , status = '" << user["status"] << "'  , Mobile_number = '" << user["mobile_number"] << "' WHERE acc_num = '" << user["acc_no"] << "'";
    string query = ss.str();
    const char *q = query.c_str();
    qstate = mysql_query(conn, q);

    if (qstate == 0)
        cout << "Record Updated" << endl;
    else
        cout << "failed" << endl;

    mysql_close(conn);
}

//searches for a particular user in database through Account number
map<string, string> search(string acc_no)
{
    string dummy;
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "remotemysql.com", "mH2kQ9m8IW", "tXfgICQA3d", "mH2kQ9m8IW", 3306, NULL, 0);
    map<string, string> user;
    if (conn)
    {
        stringstream ss;
        ss << "SELECT * from ATM_users where acc_num =  '" << acc_no << "'";
        string query = ss.str();
        const char *q = query.c_str();
        int qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {
                cout << "";
                user["acc_no"] = row[0];
                user["PIN"] = row[1];
                user["name"] = row[2];
                user["balance"] = row[3];
                user["mobile_number"] = row[4];
                user["email"] = row[5];
                user["status"] = row[6];
                return user;
            }
        }
        else
        {
            return user;
        }
    }
    else
        return user;

    mysql_close(conn);
}

//function to add new transaction record of user in database(will implement in next module)
void add_trans_stat(string acc_no, string user_action, string amount, string date_time)
{
    MYSQL *conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "remotemysql.com", "mH2kQ9m8IW", "tXfgICQA3d", "mH2kQ9m8IW", 3306, NULL, 0);

    int qstate;
    stringstream ss;

    ss << "INSERT INTO ATM_users (acc_num , user_action , amount , date_time ) VALUES('" << acc_no << "' , '" << user_action << "' , '" << amount << "' , '" << date_time << "')";
    string query = ss.str();
    const char *q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0)
        cout << "Record Inserted" << endl;
    else
        cout << "failed" << endl;

    mysql_close(conn);
}

//function to view previous transactions of particular user(will implement in next module)
void previous_trans(string acc_no)
{
    string dummy;
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "remotemysql.com", "mH2kQ9m8IW", "tXfgICQA3d", "mH2kQ9m8IW", 3306, NULL, 0);
    map<string, string> user;
    if (conn)
    {
        stringstream ss;
        ss << "SELECT * from ATM_users where acc_num =  '" << acc_no << "'";
        string query = ss.str();
        const char *q = query.c_str();
        int qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            cout << "Account number : " << acc_no;
            while (row = mysql_fetch_row(res))
            {
                cout << "Action : " << row[1];
                cout << "Amount : " << row[2];
                cout << "Date and Time : " << row[3];
            }
        }
        else
        {
            cout << "Error fetching data" << endl;
        }
    }
    else
        cout << "Error fetching data" << endl;

    mysql_close(conn);
}

#endif