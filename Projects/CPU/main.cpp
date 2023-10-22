#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
#include <sstream>

using namespace std;

typedef string Address;
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
    RAM(const uint8_t ARCHITECTURE, const uint8_t ADDRESS_SIZE, const uint8_t OPCODE_SIZE, const uint8_t RAM_SIZE)
    {
        Size architecutre = ARCHITECTURE;
        Size address_size = ADDRESS_SIZE;
        Size opcode_size = OPCODE_SIZE;
        Size size = RAM_SIZE;
        memory = create_memory(size);
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
    int bin_to_dec(Data data)
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
public:
    CPU(const uint8_t ARCHITECTURE, const uint8_t ADDRESS_SIZE, const uint8_t OPCODE_SIZE)
    {
        Size architecutre = ARCHITECTURE;
        Size address_size = ADDRESS_SIZE;
        Size opcode_size = OPCODE_SIZE;
    }

    typedef int Data;
    typedef string OPCode;
    typedef int Register;
    typedef bool Flag;

    struct Instructions
    {
        OPCode LOAD = "0001";
        OPCode ADD = "0010";
        OPCode SUB = "0011";
        OPCode MUL;
        OPCode DIV;
        OPCode STORE = "0100";
        OPCode COMPARE = "0101";
        OPCode JUMP = "1000";
        OPCode JUMP_IF = "1001";
        OPCode OUT = "1111";
        OPCode IN = "1110";
    };

    class ALU
    {
    };
    class CU
    {
    public:
    private:
    };

private:
    Size architecutre;
    Size address_size;
    Size opcode_size;
};

class InputSystem
{
    typedef string Data;

public:
    vector<Data> getInput()
    {
        cout << "Waiting for input: " << endl;
        getline(cin, input);
        return input_to_data(input);
    }

private:
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
        Data first_number, second_number, operation_code;
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
            operation_code = "0010";
            break;
        case '-':
            operation_code = "0011";
        default:
            break;
        }

        data.push_back(operation_code);
        return data;
    }
};

void Bus(CPU cpu, RAM ram, InputSystem input)
{
    typedef string Data;
    vector<Data> ready_to_load = input.getInput();
    ram.write(0, ready_to_load[0]);
    ram.write(1, ready_to_load[1]);
    ram.read_memory();
}

void Output()
{
}

int main()
{
    const uint8_t ARCHITECTURE = 8;
    const uint8_t ADDRESS_SIZE = 8;
    const uint8_t OPCODE_SIZE = 4;
    const uint8_t RAM_SIZE = 16;
    RAM ram(ARCHITECTURE, ADDRESS_SIZE, OPCODE_SIZE, RAM_SIZE);
    CPU cpu(ARCHITECTURE, ADDRESS_SIZE, OPCODE_SIZE);
    InputSystem input;
    cout << "Welcome to CPU Simulator" << endl;
    Bus(cpu, ram, input);
    // Output();

    return 0;
}