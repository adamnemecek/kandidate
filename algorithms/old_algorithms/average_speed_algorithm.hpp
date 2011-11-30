/*! \file average_speed_algorithm.hpp
    \brief Содержит алгоритм "average_speed_algorithm" - метод средней скорости (1-шаговый, 2-го порядка точности, по интегральным входным данным).
*/

#pragma once
#ifndef ALGORITHMS_OLD_ALGORITHMS_AVERAGE_SPEED_ALGORITHM_H
#define ALGORITHMS_OLD_ALGORITHMS_AVERAGE_SPEED_ALGORITHM_H



#include <cmath>
#include "../algorithm.hpp"
#include "../../types/quaternion.hpp"
#include "../../types/vector3.hpp"



/*! Класс "average_speed_algorithm" - метод средней скорости (1-шаговый, 2-го порядка точности, по интегральным входным данным).
 *
 * @tparam Q Выбранная алгебра (кватернионы/бикватернионы).
 * @tparam I Выбранный тип входных данных.
 */
template <typename Q, typename I>
class average_speed_algorithm : public algorithm<Q,I> {

public:


	virtual ~average_speed_algorithm() {
	}


	//! Запускает алгоритм, возвращая полученные результаты работы.
	virtual boost::shared_ptr < output_data<Q> > execute() {
		boost::shared_ptr < output_data<Q> > result = init_output_data_();

		for (size_t i=1; i<result->get_count(); ++i) {
			I phi = input_data_->get_integrated (result->ts[i-1], result->ts[i]);
			double phi_m = phi.length();

			Q lambda (
				cos (phi_m / 2),
				phi * sin (phi_m / 2) / phi_m
			);
			(*result)[i] = lambda * (*result)[i-1];
		}

		return result;
	}


	//! Возвращает название алгоритма в виде строки.
	virtual std::string get_algorithm_title() {
		return "Метод средней скорости (1-шаговый, 2-го порядка, по интегральным данным)";
	}


}; // class average_speed_algorithm



#endif // ifndef ALGORITHMS_OLD_ALGORITHMS_AVERAGE_SPEED_ALGORITHM_H