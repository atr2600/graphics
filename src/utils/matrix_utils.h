/*
 * projection.h
 *
 *  Created on: Jun 30, 2010
 *      Author: kendy
 */

#ifndef PROJECTION_H_
#define PROJECTION_H_

#include "core/core.h"
#include "core/math3d_plugin.h"
#include "matrix44.h"
#include "core/export.h"

namespace math3d {

    EXPORT const matrix44 orthographicMatrix(const float & left, const float & right,
                                             const float & bottom, const float & top, 
                                             const float & near, const float & far);

    EXPORT const matrix44 frustumMatrix(const float & left, const float & right, const float & bottom, const float & top, const float & near, const float & far);

    EXPORT const matrix44 rotationMatrix(const float & angle, const float & x, const float & y, const float & z);

    EXPORT const matrix44 scaleMatrix(const float & sx, const float & sy, const float & sz);
    
    EXPORT const matrix44 translationMatrix(const float & x, const float & y, const float & z);
}
#endif /* PROJECTION_H_ */
