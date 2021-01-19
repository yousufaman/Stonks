// Header files
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <memory>
#include <random>
#include "Array.cpp"


using namespace std;



// Helper Functions for Simulating Black Scholes Model
void welcomeMessage();
float generateUniqueRandomNumbers(float mean, float standard_deviation); //returns a unique random number
float calculateStandardVolatility(float spot_price, int time_interval); //returns volatility
float* calculateAverage(float** matrix, int num_loops, int time_interval);  //returns array of averages
float* simulateBlackScholesModel(float spot_price, int time_interval, float risk_rate, float volatility); //returns European Callback


// Driver Function
int main()
{
    clock_t t = clock();

    // Variables Required
    int no_of_bsmodel_simulation = 100;     // Inner loop iterations
    int no_of_averages = 1000;  // Outer loop iterations
    int time_interval = 180; //in minutes
    float risk_rate = 0.001f;   // Risk free interest rate (%)
    float spot_price = 100.0f;  // Spot price (at t = 0)

    //initialise 2D Array for Stock Prediction
    float** stock = new float* [no_of_bsmodel_simulation];
    for (int i = 0; i < no_of_bsmodel_simulation; i++)
        stock[i] = new float[time_interval];

    // initialise 2D Array for Averages
    float** avg_stock = new float* [no_of_averages];
    for (int i = 0; i < no_of_averages; i++)
        avg_stock[i] = new float[time_interval];

    // Array for optimal output
    Array<float> optimal_stock(time_interval);

    welcomeMessage();

    // Calculate Volatility
    cout << "Calculating Volatility of Product Based on Input...\n";
    float volatility = calculateStandardVolatility(spot_price, time_interval);
    float* opt_stock = new float[time_interval];

    cout << std::setprecision(2) << std::fixed;
    for (int i = 0; i < no_of_averages; i++)
    {
        //nested lopp for averaging simulations
        for (int j = 0; j < no_of_bsmodel_simulation; j++)
            stock[j] = simulateBlackScholesModel(spot_price, time_interval, risk_rate, volatility); 

        avg_stock[i] = calculateAverage(stock, no_of_bsmodel_simulation, time_interval);
        cout << "End of Simulation : " << i << endl;
        cout << " estimated Call Back : " <<avg_stock[i][179] << endl;
    }

    //get optimal prices from the average of all simulations
    opt_stock = calculateAverage(avg_stock, no_of_averages, time_interval);

    // Write stocks to output file
    ofstream file_ptr;
    file_ptr.open("opt.csv", ofstream::out);
    if (!file_ptr.is_open())
    {
        exit(0);
    }

    for (int i = 0; i < time_interval; i++){
        file_ptr << opt_stock[i] << ",";
    }
    file_ptr.close();

    //Call destructors explicitly
    for (int i = 0; i < no_of_bsmodel_simulation; i++)
        delete[] stock[i];
    delete[] stock;

    for (int i = 0; i < no_of_averages; i++)
        delete[] avg_stock[i];
    delete[] avg_stock;

    delete[] opt_stock;

    t = clock() - t;
    cout << " \n\nTime Taken for execution:  " << (t / CLOCKS_PER_SEC) << "s";

    cout << "\nDone!\nEstimated Black Scholes!\nCheck OPT.CSV!\nPress Enter to End";

    getchar();
    return 0;
}


void welcomeMessage()
{
    cout << "*****************************************\n";
    cout << "*          WELCOME   TO  STONKS         *\n";
    cout << "*****************************************\n";

    cout << "\nProject Made By:\nM. Yousuf Aman";
    cout << "\nFizza Zakir\n\nPress Enter to Start Simulation\n\n";
    getchar();
}


float generateUniqueRandomNumbers(float mean, float standard_deviation) 
{
    
    // srand time(NULL);
    // int random = rand()%1 - 1;
    // for ( int i = 0; i<180; i++){
    //     if(random == UNIQUE)
    // }

    auto seed = chrono::system_clock::now().time_since_epoch().count();

    default_random_engine generator(static_cast<unsigned int>(seed));
    normal_distribution<float> distribution(mean, standard_deviation);

    return distribution(generator);
}

float calculateStandardVolatility(float spot_price, int time_interval)
{
  
    ifstream file_ptr;
    file_ptr.open("data.csv", ifstream::in);
    if (!file_ptr.is_open()){
        exit(0);
    }

    string line;
    getline(file_ptr, line);

    file_ptr.close();

    int i = 0, len = time_interval - 1;
    unique_ptr<float[]> unique_array_of_prices = make_unique<float[]>(time_interval - 1);

    istringstream iss(line);
    string token;
    //read input in array
    while (getline(iss, token, ',')){
        unique_array_of_prices[i++] = stof(token);
    }

    float sum = spot_price;
    cout << "\nSpot Price is: " << spot_price;
    

    //apply Volatility Formula to Calculate it as Standard Deviation
    for (i = 0; i < len; i++){
        sum += unique_array_of_prices[i];
    }
    float mean_price = sum / (len + 1);
    sum = powf((spot_price - mean_price), 2.0f);
    for (i = 0; i < len; i++)
        sum += powf((unique_array_of_prices[i] - mean_price), 2.0f);
    float std_dev = sqrtf(sum);


    cout << "\nVolatility is: " << std_dev << "\n";
    return std_dev / 100.0f;
}

float* calculateAverage(float** stock_input, int num_loops, int time_interval)
{
    int j;
    float* temp_average = new float[time_interval];
    float temp_sum = 0.0f;

    for (int i = 0; i < time_interval; i++)
    {
        for (j = 0; j < num_loops; j++)
        {
            temp_sum += stock_input[j][i];
        }

        // Calculating average across columns
        temp_average[i] = temp_sum / num_loops;
        temp_sum = 0.0f;
    }

    return temp_average;
}

float* simulateBlackScholesModel(float spot_price, int time_interval, float risk_rate, float volatility)
{
    float  mean = 0.0f, std_dev = 1.0f;        // Mean and standard deviation
    float  delta = 1.0f / time_interval;      // Timestep
    unique_ptr<float[]> norm_rand = make_unique<float[]>(time_interval - 1);      // Array of normally distributed random nos.
    float* stock_price = new float[time_interval];   // Array of stock price at diff. times
    stock_price[0] = spot_price;       // Stock price at t=0 is spot price

    // Populate array with random nos.
    for (int i = 0; i < time_interval - 1; i++)
        norm_rand[i] = generateUniqueRandomNumbers(mean, std_dev);

    // Run Black Scholes equation to calculate European Callback
    for (int i = 0; i < time_interval - 1; i++)
        stock_price[i + 1] = stock_price[i] * exp(((risk_rate - (powf(volatility, 2.0f) / 2.0f)) * delta) + (volatility * norm_rand[i] * sqrtf(delta)));

    
    return stock_price;
}
