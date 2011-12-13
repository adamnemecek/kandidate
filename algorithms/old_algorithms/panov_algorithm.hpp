/** \file panov_algorithm.hpp
    \brief Содержит алгоритм "panov_algorithm" - алгоритм Панова (4-шаговый, 6-го порядка точности, по интегральным входным данным).
*/

#pragma once
#ifndef ALGORITHMS_OLD_ALGORITHMS_PANOV_ALGORITHM_H
#define ALGORITHMS_OLD_ALGORITHMS_PANOV_ALGORITHM_H



#include <cmath>
#include "../iterative_algorithm.hpp"
#include "../../types/quaternion.hpp"
#include "../../types/matrix33.hpp"
#include "../../types/vector3.hpp"



/** Класс "panov_algorithm" - алгоритм Панова (4-шаговый, 6-го порядка точности, по интегральным входным данным).
 */
class panov_algorithm : public iterative_algorithm<quaternion,vector3> {

private:
	

	//! Возвращает название алгоритма в виде строки.
	virtual std::string get_algorithm_title() {
		return "Алгоритм Панова (4-шаговый, 6-го порядка, по интегральным данным)";
	}


	/** Возвращает "Шаговость" алгоритма.
	 *
	 * Шаговость - это то, во сколько раз дискретность выдачи решения
	 * меньше дискретности входных данных.
	 */
	virtual int get_algorithm_steps_count_() {
		return 4;
	}


	/** Вычисляет решение на текущем временном отрезке.
	 *
	 * @param t Время, в которое требуется найти решение.
	 * @param gamma Вектор, состоящий из единственного элемента - входных данных на текущем временном отрезке.
	 */
	virtual quaternion get_local_solution_ (double t, const std::vector<vector3> & gamma) {
		matrix33 Gamma[4];
		for (int j=0; j<4; ++j) {
			const vector3 & g = gamma[j];
			Gamma[j] = matrix33 (
				    0,   -g[2],    g[1],
				 g[2],       0,   -g[0],
				-g[1],    g[0],       0
			);
		}

		vector3 phi =
			22.0/45 * (Gamma[0] + Gamma[1]) * (gamma[2] + gamma[3]) +
			32.0/45 * (Gamma[0] * gamma[1] + Gamma[2] * gamma[3]);

		vector3 delta_phi =
			32.0/45 * (Gamma[0]*Gamma[1]*gamma[3] - Gamma[3]*Gamma[0]*gamma[2]) +
			64.0/45 * dotProduct (gamma[1], gamma[2]) * Gamma[1] * gamma[2];

			
		for (int j=0; j<4; ++j)
			phi += gamma[j];
		phi += delta_phi;


		double phi_m = phi.length();
		return quaternion (
			cos (phi_m / 2),
			phi * sin (phi_m / 2) / phi_m
		);
	}


}; // class panov_algorithm



#endif // ifndef ALGORITHMS_OLD_ALGORITHMS_PANOV_ALGORITHM_H
