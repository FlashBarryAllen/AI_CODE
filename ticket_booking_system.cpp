#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

// 定义座位类
class Seat {
public:
    int id;
    bool isBooked;
    string customerName;
    
    Seat(int seatId) : id(seatId), isBooked(false), customerName("") {}
};

// 定义航班/演出类
class Event {
public:
    string name;
    vector<Seat> seats;
    int totalSeats;
    
    Event() : name(""), totalSeats(0) {} // 默认构造函数
    
    Event(string eventName, int numberOfSeats) : name(eventName), totalSeats(numberOfSeats) {
        for(int i = 1; i <= numberOfSeats; i++) {
            seats.push_back(Seat(i));
        }
    }
    
    // 显示可用座位
    void displayAvailableSeats() {
        cout << "\n=== " << name << " 可用座位 ===" << endl;
        cout << "座位ID\t状态" << endl;
        for(auto& seat : seats) {
            cout << seat.id << "\t";
            if(seat.isBooked) {
                cout << "已预订";
            } else {
                cout << "可预订";
            }
            cout << endl;
        }
    }
    
    // 预订座位
    bool bookSeat(int seatId, string customerName) {
        if(seatId < 1 || seatId > totalSeats) {
            cout << "错误：座位ID超出范围！" << endl;
            return false;
        }
        
        if(seats[seatId-1].isBooked) {
            cout << "座位 " << seatId << " 已被预订，请选择其他座位。" << endl;
            return false;
        }
        
        seats[seatId-1].isBooked = true;
        seats[seatId-1].customerName = customerName;
        cout << "成功预订座位 " << seatId << " 给 " << customerName << "！" << endl;
        return true;
    }
    
    // 取消预订
    bool cancelBooking(int seatId) {
        if(seatId < 1 || seatId > totalSeats) {
            cout << "错误：座位ID超出范围！" << endl;
            return false;
        }
        
        if(!seats[seatId-1].isBooked) {
            cout << "座位 " << seatId << " 当前未被预订，无法取消。" << endl;
            return false;
        }
        
        string customerName = seats[seatId-1].customerName;
        seats[seatId-1].isBooked = false;
        seats[seatId-1].customerName = "";
        cout << "成功取消 " << customerName << " 在座位 " << seatId << " 的预订！" << endl;
        return true;
    }
    
    // 查看预订详情
    void viewBookingDetails(int seatId) {
        if(seatId < 1 || seatId > totalSeats) {
            cout << "错误：座位ID超出范围！" << endl;
            return;
        }
        
        Seat& seat = seats[seatId-1];
        cout << "\n=== 座位 " << seatId << " 详情 ===" << endl;
        cout << "状态：" << (seat.isBooked ? "已预订" : "可预订") << endl;
        if(seat.isBooked) {
            cout << "客户姓名：" << seat.customerName << endl;
        }
    }
    
    // 获取可用座位数量
    int getAvailableSeatsCount() {
        int count = 0;
        for(auto& seat : seats) {
            if(!seat.isBooked) {
                count++;
            }
        }
        return count;
    }
};

// 订票系统管理类
class TicketBookingSystem {
private:
    map<string, Event> events;
    
public:
    // 添加活动（航班/演出）
    void addEvent(string eventName, int numberOfSeats) {
        events[eventName] = Event(eventName, numberOfSeats);
        cout << "成功添加活动: " << eventName << " (" << numberOfSeats << "个座位)" << endl;
    }
    
    // 显示所有活动
    void displayEvents() {
        if(events.empty()) {
            cout << "当前没有活动。" << endl;
            return;
        }
        
        cout << "\n=== 所有活动 ===" << endl;
        for(auto& pair : events) {
            Event& event = pair.second;
            cout << "活动: " << event.name 
                 << ", 总座位数: " << event.totalSeats 
                 << ", 剩余座位: " << event.getAvailableSeatsCount() << endl;
        }
    }
    
    // 预订座位
    void bookTicket(string eventName, int seatId, string customerName) {
        auto it = events.find(eventName);
        if(it == events.end()) {
            cout << "错误：活动 \"" << eventName << "\" 不存在！" << endl;
            return;
        }
        
        it->second.bookSeat(seatId, customerName);
    }
    
    // 取消预订
    void cancelBooking(string eventName, int seatId) {
        auto it = events.find(eventName);
        if(it == events.end()) {
            cout << "错误：活动 \"" << eventName << "\" 不存在！" << endl;
            return;
        }
        
        it->second.cancelBooking(seatId);
    }
    
    // 查看座位详情
    void viewBookingDetails(string eventName, int seatId) {
        auto it = events.find(eventName);
        if(it == events.end()) {
            cout << "错误：活动 \"" << eventName << "\" 不存在！" << endl;
            return;
        }
        
        it->second.viewBookingDetails(seatId);
    }
    
    // 显示活动的可用座位
    void displayAvailableSeats(string eventName) {
        auto it = events.find(eventName);
        if(it == events.end()) {
            cout << "错误：活动 \"" << eventName << "\" 不存在！" << endl;
            return;
        }
        
        it->second.displayAvailableSeats();
    }
    
    // 运行系统
    void run() {
        cout << "欢迎使用订票系统！" << endl;
        
        // 添加一些示例活动
        addEvent("北京-上海 航班 CA1837", 50);
        addEvent("周杰伦演唱会", 100);
        addEvent("红楼梦话剧", 80);
        
        int choice;
        string eventName, customerName;
        int seatId;
        
        while(true) {
            cout << "\n=== 订票系统菜单 ===" << endl;
            cout << "1. 查看所有活动" << endl;
            cout << "2. 查看活动的可用座位" << endl;
            cout << "3. 预订座位" << endl;
            cout << "4. 取消预订" << endl;
            cout << "5. 查看预订详情" << endl;
            cout << "6. 退出系统" << endl;
            cout << "请选择操作 (1-6): ";
            
            cin >> choice;
            
            switch(choice) {
                case 1:
                    displayEvents();
                    break;
                    
                case 2:
                    cout << "请输入活动名称: ";
                    cin.ignore(); // 清除输入缓冲区
                    getline(cin, eventName);
                    displayAvailableSeats(eventName);
                    break;
                    
                case 3:
                    cout << "请输入活动名称: ";
                    cin.ignore(); // 清除输入缓冲区
                    getline(cin, eventName);
                    cout << "请输入座位ID: ";
                    cin >> seatId;
                    cout << "请输入客户姓名: ";
                    cin.ignore(); // 清除输入缓冲区
                    getline(cin, customerName);
                    bookTicket(eventName, seatId, customerName);
                    break;
                    
                case 4:
                    cout << "请输入活动名称: ";
                    cin.ignore(); // 清除输入缓冲区
                    getline(cin, eventName);
                    cout << "请输入要取消的座位ID: ";
                    cin >> seatId;
                    cancelBooking(eventName, seatId);
                    break;
                    
                case 5:
                    cout << "请输入活动名称: ";
                    cin.ignore(); // 清除输入缓冲区
                    getline(cin, eventName);
                    cout << "请输入座位ID: ";
                    cin >> seatId;
                    viewBookingDetails(eventName, seatId);
                    break;
                    
                case 6:
                    cout << "感谢使用订票系统，再见！" << endl;
                    return;
                    
                default:
                    cout << "无效选择，请重新输入！" << endl;
                    break;
            }
        }
    }
};

int main() {
    TicketBookingSystem system;
    system.run();
    return 0;
}