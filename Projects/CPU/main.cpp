#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
#include <sstream>
#include <unordered_map>

using namespace std;

typedef string Address;
typedef string OPCode;
typedef uint8_t Size;

string dec_to_bin(int dec)
{
    string binary = "";
    while (dec > 0)
    {
        binary = to_string(dec % 2) + binary;
        dec /= 2;
    }
    while (binary.length() < 4)
    {
        binary = "0" + binary;
    }
    return binary;
}

class RAM
{
public:
    typedef string Data;
    typedef vector<vector<Data>> Memory;
    RAM(const uint8_t RAM_SIZE)
    {
        Size size = RAM_SIZE;
        memory = create_memory(size);
    }
    Memory get_memory()
    {
        return memory;
    }
    Memory read_memory()
    {
        for (int i = 0; i < memory.size(); i++)
        {
            cout << "Address: " << memory[i][0] << " | Value: " << memory[i][1] << endl;
        }
        return memory;
    }
    Data read(uint8_t dec_address)
    {
        if (check_address(dec_address))
        {
            Address address = dec_to_address(dec_address);
            cout << "Address: " << address << " | Value: " << memory[dec_address][1] << endl;
        }
        return memory[dec_address][1];
    }

    Data write(uint8_t dec_address, uint8_t value)
    {
        if (check_address(dec_address))
        {
            Data data = dec_to_data(value);
            memory[dec_address][1].replace(memory[dec_address][1].length() - 4, 4, data);
            cout << "Memory Updated (Write)" << endl;
        }
        return memory[dec_address][1];
    }

    Data write(uint8_t dec_address, string value)
    {
        if (check_address(dec_address))
        {
            Data data = value;
            memory[dec_address][1].replace(memory[dec_address][1].length() - 4, 4, data);
            cout << "Memory Updated (Write)" << endl;
        }
        return memory[dec_address][1];
    }

    OPCode write_opcode(uint8_t dec_address, OPCode opcode)
    {
        if (check_address(dec_address))
        {
            memory[dec_address][1].replace(0, 4, opcode);
            cout << "Memory Updated (Write)" << endl;
        }
        return memory[dec_address][1];
    }
    Data remove(uint8_t dec_address)
    {
        if (check_address(dec_address))
        {
            memory[dec_address][1] = "";
            cout << "Memory Updated (Remove)" << endl;
        }
        return memory[dec_address][1];
    }
    Address value_to_address(uint8_t value)
    {
        Data data = dec_to_data(value);

        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i][1].substr(4, 4) == data)
            {
                cout << "The address of value: " << value << " is: " << memory[i][0] << endl;
                return memory[i][0];
            }
        }
        cout << "Address not found" << endl;
        return "";
    }
    Address value_to_address(Data data)
    {
        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i][1] == data)
            {
                cout << "The address of value: " << data << " is: " << memory[i][0] << endl;
                return memory[i][0];
            }
        }
        cout << "Address not found" << endl;
        return "";
    }
    Data address_to_value(uint8_t dec_address)
    {
        Address address = dec_to_address(dec_address);
        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i][0] == address)
            {
                cout << "Value found at address: " << memory[i][1].substr(4, 4) << endl;
                return memory[i][1];
            }
        }
        cout << "Value not found" << endl;
        return "";
    }

private:
    Memory memory;
    Size size;
    Size opcode_size;

    Memory create_memory(uint8_t size)
    {
        Memory memory_grid;
        for (int i = 0; i < size; i++)
        {
            vector<Data> row;
            row.push_back(dec_to_address(i)); // address
            row.push_back("00000000");        // value
            memory_grid.push_back(row);
        }
        return memory_grid;
    }
    Address dec_to_address(uint8_t dec_address)
    {
        Address address = "0x00";
        string string_address;
        if (dec_address <= 9)
        {
            string_address = "0" + to_string(dec_address);
        }
        else
        {
            string_address = to_string(dec_address);
        }

        for (int i = 0; i < string_address.length(); i++)
        {
            address += string_address[i];
        }
        return address;
    }
    Data dec_to_data(uint8_t dec)
    {
        Data data = dec_to_bin(dec);
        return data;
    }
    int data_to_dec(Data data)
    {
        int dec = stoi(data, nullptr, 2);
        return dec;
    }
    bool check_address(uint8_t dec_address)
    {
        Address address = dec_to_address(dec_address);
        for (int i = 0; i < memory.size(); i++)
        {
            if (address == memory[i][0])
            {
                return true;
            }
        }
        cout << "Address not found" << endl;
        return false;
    }
};

class CPU
{
    typedef int Data;
    typedef string Register;
    typedef bool Flag;

public:
    CPU(RAM &MEMORY) : ram(MEMORY) {}
    struct Registers
    {
        Register A = "01";
        Register B = "10";
    };
    Registers regist;

    struct Flags
    {
        Flag zero;
        Flag positive;
        Flag negative;
    };
    Flags flag;

    // Using unordered_map instead of a struct for efficiency
    unordered_map<string, string> opcode = {
        {"LOAD", "0001"},
        {"ADD", "0010"},
        {"SUB", "0011"},
        {"STORE", "0100"},
        {"HALT", "1111"}};

    vector<vector<string>> fetch(vector<string> data)
    {
        vector<vector<string>> fetched_memory = ram.get_memory();
        vector<vector<string>> simplified_memory;

        if (fetched_memory[fetched_memory.size() - 1][1].substr(4, 4) == opcode["HALT"])
        {
            simplified_memory = fetched_memory;
        }
        else
        {
            for (int i = 0; i < fetched_memory.size(); i++)
            {
                if (fetched_memory[i][1].substr(0, 4) == opcode["HALT"])
                {
                    break;
                }
                simplified_memory.push_back({fetched_memory[i][0], fetched_memory[i][1]});
            }
        }
        // TEST PURPOSES
        cout << simplified_memory.size() << endl;
        for (int i = 0; i < simplified_memory.size(); i++)
        {
            cout << "Address: " << simplified_memory[i][0] << " | Value: " << simplified_memory[i][1] << endl;
        }
        return simplified_memory;
    }

private:
    RAM &ram;
    int bin_to_dec(string data)
    {
        int decimal = 0;
        int power = 0;

        for (int i = data.length() - 1; i >= 0; --i)
        {
            if (data[i] == '1')
            {
                decimal += (1 << power);
            }
            power++;
        }
        return decimal;
    }

    OPCode read_opcode(uint8_t dec_address)
    {
        string memory_cell = ram.read(dec_address);
        memory_cell = memory_cell.substr(0, 4);

        auto iterator = opcode.find(memory_cell); // Return the iterator containg the opcode in map
        if (iterator != opcode.end())
        {
            return iterator->second; // if found the value (ADD: "0010") returns "0010"
        }
    }
    Data read_value(uint8_t dec_address)
    {
        string memory_cell = ram.read(dec_address);
        memory_cell = memory_cell.substr(4, 4);
        return bin_to_dec(memory_cell);
    }
};

class InputSystem
{
    typedef string Data;

public:
    InputSystem(RAM &MEMORY, CPU &CPU) : ram(MEMORY), cpu(CPU) {}
    vector<Data> getInput()
    {
        cout << "Waiting for input: " << endl;
        getline(cin, input);
        vector<Data> ready_to_load = input_to_data(input);
        ram.write_opcode(0, cpu.opcode["LOAD"]);
        ram.write(0, ready_to_load[0]);
        ram.write_opcode(1, cpu.opcode["LOAD"]);
        ram.write(1, ready_to_load[1]);
        ram.write_opcode(2, ready_to_load[2]);
        ram.write(2, cpu.regist.A + cpu.regist.B);
        ram.write_opcode(3, cpu.opcode["HALT"]);
        ram.read_memory();
        return ready_to_load;
    }

private:
    RAM &ram;
    CPU &cpu;
    string input;
    vector<Data> input_to_data(string input)
    {
        string formatted_input;

        for (char c : input)
        {
            if (!isspace(c))
            {
                formatted_input += c;
            }
        }

        istringstream iss(formatted_input);
        int num1 = 0, num2 = 0;
        char op = '\0';
        Data first_number, second_number;
        OPCode operation_code;
        vector<Data> data;

        if (iss >> num1 >> op >> num2)
        {
            first_number = dec_to_bin(num1);
            second_number = dec_to_bin(num2);
            data.push_back(first_number);
            data.push_back(second_number);
        }
        else
        {
            cerr << "Invalid Input" << endl;
            return vector<Data>();
        }

        switch (op)
        {
        case '+':
            operation_code = cpu.opcode["ADD"];
            break;
        case '-':
            operation_code = cpu.opcode["SUB"];
        default:
            break;
        }

        data.push_back(operation_code);
        return data;
    }
};

void Bus(CPU cpu, RAM ram, InputSystem input)
{
}

void Output()
{
}

int main()
{
    const uint8_t RAM_SIZE = 16;
    RAM ram(RAM_SIZE);
    CPU cpu(ram);
    InputSystem input(ram, cpu);
    cout << "Welcome to CPU Simulator" << endl;
    vector<string> data = input.getInput();
    cpu.fetch(data);
    // Output();

    return 0;
}