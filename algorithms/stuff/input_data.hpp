/** \file input_data.hpp
    \brief Содержит класс "input_data" - абстрактный источник входных данных для алгоритма (см. класс algorithm).
*/

#pragma once
#ifndef ALGORITHMS_STUFF_INPUT_DATA_H
#define ALGORITHMS_STUFF_INPUT_DATA_H



#include <stdexcept>



/** Класс "input_data" - абстрактный источник входных данных для алгоритма (см. класс algorithm).
 *
 * Бывает два типа входных данных: мгновенные ("instanteous" - данные в
 * конкретный момент времени) и интегральные ("integrated" - сумма за целый
 * отрезок времени). Данный класс предоставляет два соответствующих метода
 * для получения тех или иных данных.
 *
 * Основная идея - в том, что мы не фиксируем заранее, мгновенные или
 * интегральные данные понадобятся для алгоритма, и классы-потомки не обязаны
 * реализовывать оба типа входных данных. Поэтому обе реализации по умолчанию
 * просто бросают исключение, и если какой-либо алгоритм потребует входные
 * данные, для которых класс-потомок input_data не предоставит реализацию, то
 * дело дойдёт до этого исключения.
 *
 * @tparam Q Выбранная алгебра (кватернионы/бикватернионы).
 * @tparam I Выбранный тип входных данных.
 */
template <typename Q, typename I>
class input_data {

public:


	virtual ~input_data() {
	}


	//! Возвращает начальные данные - т.е. решение в момент времени t=0.
	virtual typename Q get_initial_solution() = 0;


	/** Возвращает мгновенные входные данные в данный момент времени.
	 *
	 * По умолчанию кидает исключение, т.е. классы-потомки должны
	 * переопределять этот метод, если планируется использовать
	 * мгновенные входные данные.
	 *
	 * @throws std::runtime_exception Всегда кидает это исключение, если вызов дошёл до данной реализации.
	 */
	virtual typename I get_instanteous (double t) {
		throw std::runtime_error ("Not implemented: instanteous input data was not calculated.");
	}

	/** Возвращает интегральные входные данные за указанный промежуток времени.
	 *
	 * По умолчанию кидает исключение, т.е. классы-потомки должны
	 * переопределять этот метод, если планируется использовать
	 * мгновенные входные данные.
	 *
	 * @throws std::runtime_exception Всегда кидает это исключение, если вызов дошёл до данной реализации.
	 */
	virtual typename I get_integrated (double t1, double t2) {
		throw std::runtime_error ("Not implemented: integrated input data was not calculated.");
	}


}; // class input_data



#endif // ifndef ALGORITHMS_STUFF_INPUT_DATA_H
