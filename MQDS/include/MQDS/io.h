//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_INPUT_H
#define MQDS_INPUT_H
#include <vector>
#include <string>
#include <fstream>
//#include "MQDS/universe.h"
namespace MQDS
{
    class IO
    {
    public:
        IO();

        void const write_run_parameters();

        void static write_error(std::string const &to_write);

        void static write_warning(std::string const &to_write);

        std::string const &method() const { return method_; };

        std::string const &calculation() const { return calculation_; };

        std::string const &window_shape() const { return window_shape_; };

        std::string const &system_basis() const { return system_basis_; };

        std::string const &bath_potential() const { return bath_potential_; };

        int const &ntraj() const { return ntraj_; };

        int const &nstate() const { return nstate_; };

        int const &nstep() const { return nstep_; };

        int const &nlit() const { return nlit_; };

        int const &dump() const { return dump_; };

        int const &initstate() const { return initstate_; };

        int const &initstatet() const { return initstatet_; };

        int const &nbath() const { return nbath_; };

        int const &nosc() const { return nosc_; };

        double const &temperature() const { return temperature_; };

        double const &zpe() const { return zpe_; };

        double const &runtime() const { return runtime_; };


    private:
        // FUNCTIONS
        void const read_runfile();

        void const set_defaults();

        void const assign_value(std::string const &key,
                                std::vector<std::string> const &tokens);

        void static write_to_runlog(std::string const &to_write);

        void static error_out();

        // MAPS AND VECTORS
        std::vector<std::string> static const runfile_keywords;

        // INTEGERS
        int nstate_, ntraj_, nstep_, nlit_;
        int dump_, initstate_, initstatet_, nbath_, nosc_;

        // STRINGS
        std::string method_, calculation_, window_shape_;
        std::string system_basis_, bath_potential_;

        // DOUBLES
        double temperature_;
        double zpe_;
        double runtime_;
    protected:
    };
};

#endif //MQDS_INPUT_H
