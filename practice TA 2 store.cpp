#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <iomanip>
using namespace std;
struct product
{
    string commodityـname;//1
    int commodity_inventory;//2
    int commodity_price;//3
    string customer_name;//نام مشتری4
    string customer_last_name;//نام خانوادگی مشتری5
    string customer_phone_number;//شماره تلفن مشتری6
    string date;//تاریخ ثبت سفارش7
    int number_of_types_of_goods;//تعداد انواع کالا8
    int customer_commodity_index[100];//ایندکس کالاهای سفارش داده شده9
    int number_of_commodity[100];//تعداد کالای سفارش داده شده10
    int the_final_price;//قیمت نهایی سفارش11
};
class store
{
private:
    product a[1000];
public:
    fstream file[14];
    void add_commodity();
    void commodities();
    void place_an_order();
    void view_orders();
    void Turnover();
    void create_folder_and_file();
    void write();
    void read();
    void close_file();
    string current_time1();
}c;
int i = 0, k = 0;//12,13
int max(int arr[], int size);
string n_characters(int t, string s);
string string_year(int year);
void graph(string date1, string date2, int t[]);
int main()
{
    c.create_folder_and_file();
    c.read();
    int x;
    while (true)
    {
        cout << "\nsabt mahsool:1 , mahsoolat:2 , sabt sefaresh:3 , sefareshat:4 , gardesh mali:5 , Terminate the program:-1 \n";
        cin >> x;
        if (x == 1)
            c.add_commodity();
        else if (x == 2)
            c.commodities();
        else if (x == 3)
            c.place_an_order();
        else if (x == 4)
            c.view_orders();
        else if (x == 5)
            c.Turnover();
        else break;
    }
    c.write();
    c.close_file();
}
void store::add_commodity()//ثبت محصول
{
    cout << "Enter the product name\n";
    cin >> a[i].commodityـname;//دریافت نام کالای جدید
    cout << "Enter the inventory\n";
    cin >> a[i].commodity_inventory;//دریافت موجودی کالای جدید
    cout << "Enter the price of the product\n";
    cin >> a[i].commodity_price;//دریافت قیمت کالای جدید
    i++;
    cout << "add Product done.\n";
}
void store::commodities()//محصولات
{
    int x;
    cout << setw(6) << setfill(' ') <<right<< "cod|" << setw(18) << "Product name|" << setw(10) << "inventory|" << setw(11) << "Price|"<<"\n";
    cout << setw(6) << setfill('-') <<"|"<< setw(18) << "|" <<setw(10)<<"|"<<setw(11)<<"|"<< "\n" << setfill(' ');
    for (int j = 0; j < i; j++)
    {

        cout <<setw(4)<<j<<" | " <<setw(15)<< a[j].commodityـname <<" | "<< setw(7) << a[j].commodity_inventory <<" | "<<setw(8)<<a[j].commodity_price<<" |"<< "\n";
    }
    while (true)
    {
        cout << "If you want to change the inventory of a product, enter its code\nOtherwise, enter -1\n";
        cin >> x;
        if (x >= 0 && x < i)
        {
            cout << "Enter the new inventory\n";
            cin >> a[x].commodity_inventory;
            cout << "done\n";
        }
        else break;
    }
}
void store::place_an_order()//ثبت سفارش
{
    int d, x;
    string date1, date2, year1, month1, day1, hour1;
    a[k].the_final_price = 0;
    cout << "Enter the number of types of products you want to order\n";
    cin >> a[k].number_of_types_of_goods;//تعداد نوع کالاهایی که میخواد سفارش بده
    for (int j = 0; j < a[k].number_of_types_of_goods; j++)
    {
        cout << "Enter the desired product ID.\nAnd then enter the number you want.\n";
    lbl_for: cin >> a[k].customer_commodity_index[j] >> a[k].number_of_commodity[j];
        if (a[a[k].customer_commodity_index[j]].commodity_inventory < a[k].number_of_commodity[j])
        {
            cout << "Insufficient inventory\n" << "There are " << a[a[k].customer_commodity_index[j]].commodity_inventory << " items in stock\n";
            if (a[a[k].customer_commodity_index[j]].commodity_inventory == 0)
            {
                a[k].number_of_commodity[j] = 0;
                continue;
            }
            else goto lbl_for;
        }
        else
        {
            a[a[k].customer_commodity_index[j]].commodity_inventory -= a[k].number_of_commodity[j];
            a[k].the_final_price += a[k].number_of_commodity[j] * a[a[k].customer_commodity_index[j]].commodity_price;
        }
    }
    cout << "Enter your first name, then your last name, then your phone number\n";
    cin >> a[k].customer_name >> a[k].customer_last_name >> a[k].customer_phone_number;
    cout << "If you want to enter the date manually enter the number 1\n"<<"Otherwise number -1\n";
    cin >> x;
    if (x == 1)
    {
        cout << "Enter the year: ";
        cin >> year1;
        cout << "\t month: ";
        cin >> month1;
        cout << "\t   day: ";
        cin >> day1;
        cout << "\t  hour: ";
        cin >> hour1;
        a[k].date = year1 + " " + month1 + " " + day1 + " " + hour1;
    }
    else
        a[k].date = current_time1();
    cout << "Enter the discount percentage\n";
    cin >> d;
    d = 100 - d;
    a[k].the_final_price *= d;
    a[k].the_final_price /= 100;
    k++;
    cout << "The order was successfully placed.\n";
}
void store::view_orders()//سفارشات
{
    int x;
    for (int j = k-1; j >= 0; j--)
        cout <<"order cod: "<< j << "\t" << "Last name: " << a[j].customer_last_name << "\t" << "Final price: " << a[j].the_final_price << "\t" << "Date: " << a[j].date << "\n";
    while (true)
    {
        cout << "Enter the order code to view order details.\nOtherwise, enter -1\n";
        cin >> x;
        if (x >= 0 && x < k)
        {
            cout << setw(46) << setfill('*') <<right<< "\ninvoice id:" << x << "\n" << setfill(' ') << "Name: " << a[x].customer_name << "\t" << "Last name: " << a[x].customer_last_name << "\n" << "Phone number: " << a[x].customer_phone_number << "\n" << "Date: " << a[x].date << "\n\n";
            cout<< setw(5) << "|" << setw(18) << "product name|" << setw(8) << "number|" << setw(11) << "Unit price|" << setw(12) << "Final Price|"<<"\n";
            cout << setw(5)<<setfill('-')<<"|"<<setw(18)<<"|"<<setw(8)<<"|"<<setw(11)<<"|"<<setw(12)<<"|"<<"\n";

            for (int j = 0; j < a[x].number_of_types_of_goods; j++)
            {
                cout <<setw(3)<<setfill(' ')<<j + 1 << " |" << setw(16) << a[a[x].customer_commodity_index[j]].commodityـname << " |" << setw(6) << a[x].number_of_commodity[j] << " |" << setw(9) << a[a[x].customer_commodity_index[j]].commodity_price << " |" << setw(11) << a[a[x].customer_commodity_index[j]].commodity_price * a[x].number_of_commodity[j] << "|\n";
            }
            cout << "\nFinal price: " << a[x].the_final_price << "\n" << setw(46) << setfill('*') << "\n";
        }
        else break;
    }
}
void store::Turnover()//گردش مالی
{
    int x, s = 0, number, f[1000], o;
    for (int j2 = 0; j2 < i; j2++)
        f[j2] = 0;
    string date1, date2, year1, month1, day1, hour1, year2, month2, day2, hour2, y;
    cout << "If you want the turnover of the last month to be displayed by default, enter the 1\nOtherwise, enter the 2\n";
    cin >> x;
    if (x == 1)
    {
        date2 = current_time1();
        date1 = date2;
        if (date2.substr(6, 2) != "01")
        {
            number = stoi(date2.substr(6, 2));
            number--;
            if (number < 10)
            {
                y = "0" + to_string(number);
            }
            else y = to_string(number);
            date1.replace(5, 2, y);
        }
        else
        {
            number = stoi(date1.substr(0, 4));
            number--;
            y = to_string(number);
            date1.replace(0, 4, y);
            date1.replace(5, 2, "12");
        }
    }
    else if (x == 2)
    {
        cout << "Enter the beginning of the time range:\nEnter the year: ";
        cin >> year1;
        cout << "\t month: ";
        cin >> month1;
        cout << "\t   day: ";
        cin >> day1;
        cout << "\t  hour: ";
        cin >> hour1;
        cout << "\tEnter the end of the time range:\nEnter the year: ";
        cin >> year2;
        cout << "\t month: ";
        cin >> month2;
        cout << "\t   day: ";
        cin >> day2;
        cout << "\t  hour: ";
        cin >> hour2;
        date1 = year1 + " " + month1 + " " + day1 + " " + hour1;
        date2 = year2 + " " + month2 + " " + day2 + " " + hour2;
    }
    int l2=0, t[1000];
    string l1 = date1.substr(5, 2);
    t[0] = 0;
    cout << setw(65) << setfill('*') << "\n" << setfill(' ');
    cout << "orders:\n";
    for (int j = 0; j < k; j++)
    {
        if (a[j].date >= date1 && a[j].date <= date2)
        {
            for (int j1 = 0; j1 < a[j].number_of_types_of_goods; j1++)
            {
                o = a[j].number_of_commodity[j1];
                f[a[j].customer_commodity_index[j1]] += o;
            }
        lbl_for1: if (a[j].date.substr(5, 2) == l1)
        {
            t[l2] += a[j].the_final_price;
        }
        else
        {
            int u = stoi(l1) + 1;
            if (u < 10)
                l1 = "0" + to_string(u);
            else if (u == 13)
                l1 = "01";
            else l1 = to_string(u);
            l2++;
            t[l2] = 0;
            goto lbl_for1;
        }
            cout <<"order "<<j+1<<": \tDate: "<< a[j].date << "\t" <<"Final price: "<< a[j].the_final_price << "\n";
            s += a[j].the_final_price;
        }
    }
    cout << setw(65) << setfill('*') << "\n" << setfill(' ');
    cout << "The amount of goods sold : \n";
    cout << setw(6) << "cod|" << setw(18) << "Product name |"<< setw(8)<<"number |"<<setw(11)<<"Unit price |"<<setw(12)<<"Final price |\n";
    cout << setw(6) << setfill('-') << "|" <<setw(18)<<"|"<<setw(8)<<"|"<<setw(12)<<"|"<<setw(14)<< "|\n" << setfill(' ');
    for (int j3 = 0; j3 < i; j3++)
    {
        cout <<setw(4)<<j3<<" | " << setw(15) << a[j3].commodityـname <<" | " << setw(5) << f[j3] <<" | "<< setw(9) << a[j3].commodity_price <<" | " << setw(10) << a[j3].commodity_price * f[j3] <<" |" << "\n";
    }
    cout << '\n';
    string date11 = date1.substr(0, 7), date22 = date2.substr(0, 7);
    cout << setw(66) << setfill('*') << "\n" << setfill(' ') << "the chart:\n";
    graph(date11, date22, t);
    cout << setw(65) << setfill('*') << "\n" << setfill(' ');
    cout << "\ntotal= " << s;
    cout << setw(65) << setfill('*') << "\n" << setfill(' ');
}

int max (int arr[], int size)
{
  int max = arr[0];
  for (int i = 1; i < size; i++)
    {
      if (arr[i] > max)
        {
          max = arr[i];
        }
    }
  return max;
}

string n_characters (int t, string s){
    string a;
    for (int i=0; i<t; i++){
        a=a+s;
    }
    return a;
}

string string_year(int year){
    year = year % 100;
    if (year < 10){
        return ("0" + to_string (year));
    }
    return to_string(year);
}

void graph (string date1,string date2, int t[])
{

  const int max_blocks = 8;
  cout << "\n\n";

  int year1 = stoi(date1.substr (0, 4));
  int month1 = stoi(date1.substr (5, 7));
  int year2 = stoi(date2.substr (0, 4));
  int month2 = stoi(date2.substr (5, 7));

  int months_count = (year2-year1)*12 + month2-month1 +1;

  //int months_count = sizeof (t) / sizeof (t[0]);
  int block_value = int(max(t,months_count) / max_blocks)+1;
  string month_names[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

  for (int i = 0; i < months_count; i++){
    t[i] = int ((t[i] / block_value) +1);
    }

  int max_number_length = (to_string(block_value*max_blocks)).length();
  //cout << string(max_number_length,' ') << char(30) << "\n";

  for (int i = 0; i < max_blocks; i++)
    {
        cout << left << setw(max_number_length) << block_value*(max_blocks-i);
        cout << char(215); //"╫"
        for (int j = 0; j < months_count; j++)
        {
            cout << ' ';
            if ((max_blocks - i) <= t[j])
                cout << char(219) << "  "; //█
            else
                cout << "   ";
        }
        cout << '\n';
    }
    cout << n_characters(max_number_length," ");
    cout << char(200) <<n_characters(months_count,string(1,char(205))+string(1,char(216))+string(2,char(205))) /*<< char(16)*/ << '\n'; //"╚","═╧══"
    cout << " ";
    cout << n_characters(max_number_length, " ");
    for (int i = month1; i < month1 + months_count; i++) {
        cout << month_names[(i - 1) % 12] << " ";
    }
    cout << "\n ";
    cout << n_characters(max_number_length, " ");
    int current_year = year1;
    for (int i = month1; i < month1 + months_count; i++) {
        cout << string_year(current_year) << "  ";
        if (i == 12) {
            current_year += 1;
        }
    }
    cout << "\n";
}
void store::create_folder_and_file()
{
    bool flag = false;
    string foldername = "appfolder";
    string command = "mkdir " + string(foldername);
    if (system(command.c_str()) != 0)
    {
        cerr << "There was an error creating the folder\n";
        flag = true;
    }
    for (int j = 1; j < 14; j++)
    {
        string path = "appfolder/file" + to_string(j) + ".txt";
        if (flag)
            file[j].open(path);
        else
        {
            file[j].open(path, std::fstream::out);
        }
        if (!(file[j].is_open()))
            cout << "Error opening the file" + to_string(j) + ".txt\n";
    }
    for (int j = 12; j < 14; j++)
    {
        file[j].seekp(0, std::ios::end);
        if (file[j].tellp() == 0)
            file[j] << "0\n";
    }
}
void store::read()
{
    for (int j = 12; j < 14; j++)
        file[j].seekg(0, std::ios::beg);
    file[12] >> i;
    file[13] >> k;
    for (int j=0;j<i; j++)
    {
        file[1] >> a[j].commodityـname;
        file[2] >> a[j].commodity_inventory;
        file[3] >> a[j].commodity_price;
    }
    for (int j=0;j<k; j++)
    {
        file[4] >> a[j].customer_name;
        getline(file[5], a[j].customer_last_name);
        getline(file[6], a[j].customer_phone_number);
        getline(file[7], a[j].date);
        file[8] >> a[j].number_of_types_of_goods;
        for (int l = 0; l < a[j].number_of_types_of_goods; l++)
        {
            file[9] >> a[j].customer_commodity_index[l];
            file[10] >> a[j].number_of_commodity[l];
        }
        file[11] >> a[j].the_final_price;
    }
}
void store::write()
{
    for (int j = 1; j < 14; j++)
        file[j].seekp(0, std::ios::beg);
    for (int j = 0; j < i; j++)
    {
        file[1] << a[j].commodityـname << "\n";
        file[2] << a[j].commodity_inventory << "\n";
        file[3] << a[j].commodity_price << "\n";
    }
    for (int j = 0; j < k; j++)
    {
        file[4] << a[j].customer_name << "\n";
        file[5] << a[j].customer_last_name << "\n";
        file[6] << a[j].customer_phone_number << "\n";
        file[7] << a[j].date << "\n";
        file[8] << a[j].number_of_types_of_goods << "\n";
        for (int l = 0; l < a[j].number_of_types_of_goods; l++)
        {
            file[9] << a[j].customer_commodity_index[l] << "\n";
            file[10] << a[j].number_of_commodity[l] << "\n";
        }
        file[11] << a[j].the_final_price << "\n";
    }
    for (int j = 12; j < 14; j++)
        file[j].seekp(0, std::ios::beg);
    file[12] << i << "\n";
    file[13] << k << "\n";
}
void store::close_file()
{
    for (int j = 1; j < 14; j++)
        file[j].close();
}
string store::current_time1()
{
    auto current_time = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(current_time);
    char time_str[26];
    ctime_s(time_str, sizeof(time_str), &time);
    string x = string(time_str);
    string y, x1;
    x1 = x.substr(8, 2);
    int x2 = stoi(x1);
    if (x2 < 10)
        x1 = "0" + to_string(x2);
    string s = x.substr(4, 3);
    if (s== "Jan")
        y = x.substr(20, 4) + " 01 " + x1 + " " + x.substr(11, 8);
    else if (s=="Feb")
        y = x.substr(20, 4) + " 02 " + x1 + " " + x.substr(11, 8);
    else if (s == "Mar")
        y = x.substr(20, 4) + " 03 " + x1 + " " + x.substr(11, 8);
    else if (s == "Apr")
        y = x.substr(20, 4) + " 04 " + x1 + " " + x.substr(11, 8);
    else if (s == "May")
        y = x.substr(20, 4) + " 05 " + x1 + " " + x.substr(11, 8);
    else if (s == "Jun")
        y = x.substr(20, 4) + " 06 " + x1 + " " + x.substr(11, 8);
    else if (s == "Jul")
        y = x.substr(20, 4) + " 07 " + x1 + " " + x.substr(11, 8);
    else if (s == "Aug")
        y = x.substr(20, 4) + " 08 " + x1 + " " + x.substr(11, 8);
    else if (s == "Sep")
        y = x.substr(20, 4) + " 09 " + x1 + " " + x.substr(11, 8);
    else if (s == "Oct")
        y = x.substr(20, 4) + " 10 " + x1 + " " + x.substr(11, 8);
    else if (s == "Nov")
        y = x.substr(20, 4) + " 11 " + x1 + " " + x.substr(11, 8);
    else if (s == "Dec")
        y = x.substr(20, 4) + " 12 " + x1 + " " + x.substr(11, 8);
    return y;
}
/*
"╫"  :  "||"
"█  "   : "*  "
"╚"
"═╧══"  : "=^=="
*/