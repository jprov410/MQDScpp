//
// Created by Justin Provazza on 10/9/18.
//

#include "MQDS/io.h"
#include "MQDS/units.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

namespace
{
    // Global output log file
    std::ofstream runlog("runtime.log");
    // Delimiter to separate comments
    std::string const comment_delim="//";
    // separatory line for printing in files
    std::string const line_delim =
            "-------------------------------------------------";

    // Structure to deal with input files
    struct RunLine
    {
        std::string raw;
        std::string uncommented;
        std::vector<std::string> my_tokens;
        std::string my_keyword;

        // Remove all comments from current line
        void filter_comments()
        {
            uncommented = raw.substr(0,raw.find(comment_delim));
        };

        // Find all of the tokens in uncommented line
        void find_tokens()
        {
            size_t last = 0;
            size_t next = 0;
            my_tokens.clear();
            std::istringstream ss(uncommented);
            std::string token;

            while ( ! ss.eof() )
            {
                ss >> token;
                if (token != "=") my_tokens.push_back(token);
            }
        };

        // Check if one of the tokens is an element of keyword vector
        bool const contains_keyword(std::vector<std::string>const &keywords)
        {
            filter_comments();
            find_tokens();

            for (auto &j : keywords)
            {
                if (my_tokens[0] == j){
                    my_keyword = my_tokens[0];
                    return true;
                }
            }
            return false;
        };
    };

    std::string const assign_string( std::string const &val )
    {
        return val;
    };

    int const assign_integer( std::string const &val )
    {
        return stoi(val);
    };

    double const assign_double( std::string const &val )
    {
        return stod(val);
    };
}

MQDS::IO::IO()
{
    set_defaults();
    read_runfile();
}

void const MQDS::IO::read_runfile()
{
    std::ifstream runfile;
    RunLine line;

    runfile.open("run.in");
    while (std::getline(runfile,line.raw))
    {
        if (line.contains_keyword(runfile_keywords))
        {
            //for (auto &i : line.my_tokens)
            //{
//                std::transform(i.begin(), i.end(), i.begin(), ::tolower);
//            }

            assign_value(line.my_keyword,line.my_tokens);
        }
    }
    runfile.close();
}

void const MQDS::IO::set_defaults()
{
    // INTEGER TYPE CALCULATION PARAMETERS
    ntraj_ = 100;
    nstate_ = 2;
    nstep_ = 100;
    nlit_ = 20;
    dump_ = 1;
    initstate_ = 1;
    initstatet_ = 1;

    // STRING TYPE CALCULATION PARAMETERS
    method_ = "pldm";
    calculation_ = "redmat";
    window_shape_= "square";
    system_basis_ = "site";
    bath_potential_ = "harmonic";

    // DOUBLE PRECISION TYPE CALCULATION PARAMETERS
    temperature_ = 77.0;
    zpe_ = 0.5;
}

void const MQDS::IO::assign_value(std::string const &key,
                               std::vector<std::string> const &tokens)
{
    // ASSIGN STRING VALUES
    if (key == "method") method_ = assign_string(tokens[1]);
    if (key == "calculation") calculation_ = assign_string(tokens[1]);
    if (key == "window_shape") window_shape_ = assign_string(tokens[1]);
    if (key == "system_basis") system_basis_ = assign_string(tokens[1]);
    if (key == "bath_potential") bath_potential_ = assign_string(tokens[1]);

    // ASSIGN INTEGER VALUES
    if (key == "nstate") nstate_ = assign_integer(tokens[1]);
    if (key == "ntraj") ntraj_ = assign_integer(tokens[1]);
    if (key == "nstep") nstep_ = assign_integer(tokens[1]);
    if (key == "nlit") nlit_ = assign_integer(tokens[1]);
    if (key == "dump") dump_ = assign_integer(tokens[1]);
    if (key == "initstate") initstate_ = assign_integer(tokens[1]);
    if (key == "initstatet") initstatet_ = assign_integer(tokens[1]);

    // DOUBLE PRECISION VALUES
    if (key == "temperature") temperature_ = assign_double(tokens[1]);
    if (key == "zpe") zpe_ = assign_double(tokens[1]);

}

void const MQDS::IO::write_run_parameters()
{
    // Current time
    auto time_now =
            std::chrono::system_clock::to_time_t
                    (std::chrono::system_clock::now());
    {
        if (runlog.is_open())
        {
            //MQDS::Universe::is_master();
            runlog << "~~~ Welcome to MQDS ~~~" << std::endl;
            runlog << "Simulation started " <<
                   std::ctime(&time_now);
            runlog << line_delim << std::endl;
            runlog << "Calculation parameters given as:" << std::endl;
            runlog << "method = " << method_ << std::endl;
            runlog << "calculation = " << calculation_ << std::endl;
            runlog << "system_basis = " << system_basis_ << std::endl;
            runlog << "bath_potential = " << bath_potential_ << std::endl;
            runlog << "nstate = " << nstate_ << std::endl;
            runlog << "initstate = " << initstate_ << std::endl;
            runlog << "initstatet = " << initstatet_ << std::endl;
            runlog << "ntraj = " << ntraj_ << std::endl;
            runlog << "nstep = " << nstep_ << std::endl;
            runlog << "nlit = " << nlit_ << std::endl;
            runlog << "dump = " << dump_ << std::endl;
            runlog << "temperature = " << temperature_ << std::endl;

            runlog << "-------SQC variables-------" << std::endl;
            runlog << "zpe = " << zpe_ << std::endl;
            runlog << "window_shape = " << window_shape_ << std::endl;

        }
        else std::cout << "unable to open run_info.log file" << std::endl;
    }
}

void const MQDS::IO::write_to_runlog( std::string const &to_write)
{
    if (runlog.is_open())
    {
        runlog << to_write << std::endl;
    }
}

void const MQDS::IO::write_error( std::string const &to_write)
{
    std::string error_message;
    error_message = "** ERROR: " + to_write;
    write_to_runlog(error_message);
    error_out();
}

void const MQDS::IO::write_warning( std::string const &to_write)
{
    std::string warning_message;
    warning_message = "** WARNING: " + to_write;
    write_to_runlog(warning_message);
}

void const MQDS::IO::error_out()
{

}

// Vector of keywords for the run.in file
std::vector<std::string> const MQDS::IO::runfile_keywords = {
                // CHARACTER/STRING type parameters
                "method",         // dynamics method choice
                "calculation",    // type of calculation
                "window_shape",   // SQC windowing model
                "system_basis",   // site or exciton basis
                "bath_potential", // harmonic, multiple anharmonic types

                // INTEGER type parameters
                "nstate",    // number of system states
                "ntraj",     // number of trajectories for trajectory-based methods
                "nstep",     // number of time steps in simulation
                "nlit",      // number of little steps per big step if need finer
                // integration grid
                "dump",      // number of steps per observation
                "initstate", // initial state for fwd wavefunction
                "initstatet",// initial state for bkwd wavefunction

                // DOUBLE PRECISION type parameters
                "temperature", // temperature of simulation in Kelvin
                "zpe", // temperature of simulation in Kelvin
        };

