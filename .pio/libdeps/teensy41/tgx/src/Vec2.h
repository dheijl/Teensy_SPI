/**   
 * @file Vec2.h 
 * 2D vector. 
 */
//
// Copyright 2020 Arvind Singh
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
//version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; If not, see <http://www.gnu.org/licenses/>.


#ifndef _TGX_VEC2_H_
#define _TGX_VEC2_H_

// only C++, no plain C
#ifdef __cplusplus


#include <stdint.h>
#include "Misc.h"

namespace tgx
{


    // forward declarations

    template<typename T> struct Vec2;

    template<typename T> struct Vec3;

    template<typename T> struct Vec4;


    // Specializations

    typedef Vec2<int> iVec2; ///< Integer-valued 2D vector

    typedef Vec2<float> fVec2; ///< Floating point valued 2D vector with single (float) precision

    typedef Vec2<double> dVec2; ///< Floating point valued 2D vector with double precision


    /**
     * Generic 2D vector [specializations #iVec2, #fVec2, #dVec2].
     *
     * The class contains two public member variables `x` and `y` which define the 2D vector `(x,y)`.
     * 
     * @tparam  `T` arithmetic type of the vector (`int`, `float`...)
     *
     * @sa `Vec3`,`Vec4`
     */
    template<typename T> struct Vec2
        {

        // mtools extension (if available).  
        #if (MTOOLS_TGX_EXTENSIONS)
        #include <mtools/extensions/tgx/tgx_ext_Vec2.inl>
        #endif
        
        // coordinates
        T x; ///< 'x' coordinate (first dimension)
        T y; ///< 'y' coordinate (second dimension)


        /**
         * default constructor: **the vector content is undefined**.
         */
        Vec2() {}


        /**
         * Constructor with explicit initialization.
         */
        constexpr Vec2(T X, T Y) : x(X), y(Y) {}


        /**
         * Default copy constructor.
         */
        Vec2(const Vec2 & v) = default;


        /**
        * Default assignment operator.
        **/
        Vec2 & operator=(const Vec2 & V) = default;


        /**
         * Explicit conversion to another vector with different integral type.
         *
         * @warning the conversion of the vectors components values from type `T` to type `U` is
         * performed with a simple C-style cast.
         */
        template<typename U>
        explicit operator Vec2<U>() { return Vec2<U>((U)x, (U)y); }


        /**
        * Implicit conversion to floating-point type vector. 
        **/
        operator Vec2<typename DefaultFPType<T>::fptype>() { return Vec2<typename DefaultFPType<T>::fptype>((typename DefaultFPType<T>::fptype)x, (typename DefaultFPType<T>::fptype)y); }


        /**
         * Equality comparator. Return true if all components compare equal. 
         **/
        inline bool operator==(const Vec2 V) const 
            {
            return ((x == V.x) && (y == V.y));
            }


        /**
         * Inequality operator.
         **/
        inline bool operator!=(const Vec2 V) const
            { 
            return(!(operator==(V))); 
            }


        /**
         * Less-than comparison operator. Use lexicographical order. 
         **/
        inline bool operator<(const Vec2 V) const 
            { 
            return ((x < V.x) || ((x == V.x) && (y < V.y)));
            }


        /**
         * Less-than-or-equal comparison operator. Use lexicographical order.
         **/
        inline bool operator<=(const Vec2 V) const
            {
            return ((x <= V.x) || ((x == V.x) && (y <= V.y)));
            }
            

        /**
         * Greater-than comparison operator. Use lexicographical order.
         **/
        inline bool operator>(const Vec2 V) const 
            { 
            return(!(operator<=(V))); 
            }


        /**
         * Greater-than-or-equal comparison operator. Use lexicographical order.
         **/
        inline bool operator>=(const Vec2 V) const
            { 
            return(!(operator<(V))); 
            }


        /**
        * Add another vector to this one.
        **/
        inline void operator+=(const Vec2 V)
            { 
            x += V.x;
            y += V.y;
            }


        /**
        * Substract another vector from this one.
        **/
        inline void operator-=(const Vec2 V) 
            {
            x -= V.x;
            y -= V.y;
            }


        /**
         * Multiply this vector by another one (coordinate by coordinate multiplication).
         **/
        inline void operator*=(const Vec2 V)
            {
            x *= V.x;
            y *= V.y;
            }


        /**
         * Divide this vector by another one (coordinate by coordinate division).
         **/
        inline void operator/=(const Vec2 V) 
            {
            x /= V.x;
            y /= V.y;
            }


        /**
         * scalar addition. Add v to each of the vector components. 
         **/
        inline void operator+=(const T & v) 
            {
            x += v;
            y += v;
            }


        /**
         * scalar substraction. Add v to each of the vector components.
         **/
        inline void operator-=(const T & v) 
            {
            x -= v;
            y -= v;
            }

        /**
         * scalar multiplication. Multiply each of the vector components by v.
         **/
        inline void operator*=(const T & v)
            {
            x *= v;
            y *= v;
            }

        /**
         * scalar division. Divde each of the vector components by v.
         **/
        inline void operator/=(const T & v)
            {
            x /= v;
            y /= v;
            }


        /**
         * unary negation operator
         **/
        inline Vec2 operator-() const 
            {
            return Vec2{ -x, -y };
            }


        /**
         * Compute the squared euclidian norm of the vector.
         * 
         *
         * @sa norm(), norm_fast()
        **/
        inline T norm2() const
            { 
            return x*x + y*y; 
            }


        /**
         * Compute the euclidian norm of the vector.
         *
         * @tparam  Tfloat Return type also used by computation. If left unspecified, the default
         *                 floating type is used.
         *                 
         * @sa norm_fast()
         */
        template<typename Tfloat = typename DefaultFPType<T>::fptype > inline Tfloat norm() const
            { 
            return (Tfloat)tgx::precise_sqrt((Tfloat)(x*x + y*y));
            }


        /**
         * Compute the euclidian norm of the vector. Use the #tgx::fast_sqrt() approximation to speedup
         * computations.
         *
         * @tparam  Tfloat Return type also used by computation. If left unspecified, the default
         *                 floating type is used.
         *
         * @sa norm()
         */
        template<typename Tfloat = typename DefaultFPType<T>::fptype > inline Tfloat norm_fast() const
            { 
            return (Tfloat)tgx::fast_sqrt((Tfloat)(x*x + y*y));
            }


        /**
         * Compute the inverse of the euclidian norm of the vector.
         *
         * @tparam  Tfloat Return type also used by computation. If left unspecified, the default
         *                 floating type is used.
         *
         * @sa invnorm_fast()
         */
        template<typename Tfloat = typename DefaultFPType<T>::fptype > inline Tfloat invnorm() const
            { 
            return (Tfloat)tgx::precise_invsqrt((Tfloat)(x*x + y*y));
            }


        /**
         * Compute the inverse of the euclidian norm of the vector. Use the #tgx::fast_invsqrt()
         * approximation to speedup computations.
         *
         * @tparam  Tfloat Return type also used by computation. If left unspecified, the default
         *                 floating type is used.
         *          
         * @sa invnorm()
         */
        template<typename Tfloat = typename DefaultFPType<T>::fptype > inline Tfloat invnorm_fast() const
            { 
            return (Tfloat)tgx::fast_invsqrt((Tfloat)(x*x + y*y));
            }


        /**
         * Normalise the vector so that its norm is 1 (do nothing if the vector is 0).
         *
         * @tparam  Tfloat Floating point type used for computation (use default floating point type if
         *                 unspecified).
         *
         * @sa normalize_fast()
         */
        template<typename Tfloat = typename DefaultFPType<T>::fptype > inline void normalize()
            { 
            Tfloat a = invnorm<Tfloat>(); 
            x = (T)(x * a);
            y = (T)(y * a);
            }


        /**
         * Normalise the vector so that its norm is 1 (do nothing if the vector is 0). Use
         * #fast_invsqrt() approxiamtion to speedup computations.
         *
         * @tparam  Tfloat Floating point type used for computation (use default floating point type if
         *                 unspecified).
         *
         * @sa normalize()
         */
        template<typename Tfloat = typename DefaultFPType<T>::fptype > inline void normalize_fast()
            { 
            Tfloat a = invnorm_fast<Tfloat>(); 
            x = (T)(x * a);
            y = (T)(y * a);
            }


        /**
         * Return the vector normalized to have unit norm (do nothing if the vector is 0).
         *
         * @tparam  Tfloat Floating point type used for computation (use default floating point type if
         *                 unspecified).
         *
         * @sa getNormalize_fast()
         */
        template<typename Tfloat = typename DefaultFPType<T>::fptype > inline Vec2<T> getNormalize() const
            { 
            Vec2<T> V(*this);
            V.normalize();
            return V;
            }


        /**
         * Return the vector normalized to have unit norm (do nothing if the vector is 0). Use
         * #fast_invsqrt() approxiamtion to speedup computations.
         *
         * @tparam  Tfloat Floating point type used for computation (use default floating point type if
         *                 unspecified).
         *
         * @sa getNormalize()
         */
        template<typename Tfloat = typename DefaultFPType<T>::fptype > inline Vec2<T> getNormalize_fast() const
            { 
            Vec2<T> V(*this);
            V.normalize_fast();
            return V;
            }



        /**
         * Rotate this vector by +90 degree (anti-clockise).
         */
        inline void rotate90()
            { 
            *this = getRotate90(); 
            }


        /**
         * Return the vector obtained after rotation by +90 degree (anti-clockise).
         */
        inline Vec2<T> getRotate90() const
            { 
            return Vec2<T>(-y, x); 
            }


        /**
         * Determine which half-space delimited by the line (LA,LB) the point represented by this vector
         * belongs.
         * 
         * - Returns 1 if this point is on the left of the oriented line (LA -> LB).  
         * - Returns -1 if this point is on the right of the oriented line (LA -> LB).
         * - Returns 0 if this point is located on oriented the line (LA , LB).
         */
        inline int leftOf(Vec2<T> LA, Vec2<T> LB) const;


        /**
         * Set this vector as the intersection of the two lines (LA1,LA2) and (LB1,LB2).
         * 
         * If the lines are parallel, the vector is left unchanged.
         *
         * @returns true if the intersection point was correctly computed and false if the lines are
         *          parallel.
         */
        inline bool setAsIntersection(Vec2<T> LA1, Vec2<T> LA2, Vec2<T> LB1, Vec2<T> LB2);



#ifdef TGX_ON_ARDUINO

        /**
        * Print a representation of the vector using a given stream object.
        *
        * @attention Defined only in the Arduino environment.
        */
        inline void print(Stream & outputStream = Serial) const
            {
            outputStream.printf("[%.6f \t %.6f]\n", x, y);
            }

#endif

    };



    /**
     * Return the vector normalized to have unit norm (do nothing if the vector is 0).
     *
     * @tparam Tfloat Floating point type used for computation (use default floating point type if
     *                unspecified).
     */
    template<typename T, typename Tfloat = typename DefaultFPType<T>::fptype > inline  Vec2<T> normalize(Vec2<T> V)
        {
        V.template normalize<Tfloat>();
        return V;
        }


    /**
     * Return the vector normalized to have unit norm (do nothing if the vector is 0). Use
     * fast_invsqrt() approximation to speedup computations.
     *
     * @tparam  Tfloat Floating point type used for computation (use default floating point type if
     *                 unspecified).
     */
    template<typename T, typename Tfloat = typename DefaultFPType<T>::fptype > inline  Vec2<T> normalize_fast(Vec2<T> V)
        {
        V.template normalize_fast<Tfloat>();
        return V;
        }


    /**
     * Compute the squared euclidian distance between two vectors.
     */
    template<typename T> inline T dist2(const Vec2<T>  V1, const Vec2<T>  V2)
        {
        const T xx = V1.x - V2.y;
        const T yy = V1.y - V2.y;
        return xx * xx + yy * yy;
        }


    /**
     * Compute the euclidian distance between two vectors.
     *
     * @tparam  Tfloat Floating point type used for computation (use default floating point type if
     *                 unspecified).
     */
    template<typename T, typename Tfloat = typename DefaultFPType<T>::fptype > Tfloat dist(Vec2<T> V1, const Vec2<T> V2)
        {
        const T xx = V1.x - V2.y;
        const T yy = V1.y - V2.y;
        return (Tfloat)tgx::precise_sqrt((Tfloat)(xx * xx + yy * yy));
        }


    /**
     * Compute the euclidian distance between two vectors. Use fast_sqrt() approximation to speedup
     * computations.
     *
     * @tparam  Tfloat Floating point type used for computation (use default floating point type if
     *                 unspecified).
     */
    template<typename T, typename Tfloat = typename DefaultFPType<T>::fptype > Tfloat dist_fast(Vec2<T> V1, const Vec2<T> V2)
        {
        const T xx = V1.x - V2.y;
        const T yy = V1.y - V2.y;
        return (Tfloat)tgx::fast_sqrt((Tfloat)(xx * xx + yy * yy));
        }


    /** Addition operator. Coordinates by coordinates */
    template<typename T> inline Vec2<T> operator+(Vec2<T> V1, const Vec2<T> V2) { V1 += V2; return V1; }

    /** Substraction operator. Coordinates by coordinates */
    template<typename T> inline Vec2<T> operator-(Vec2<T> V1, const Vec2<T> V2) { V1 -= V2; return V1; }

    /** Multiplication operator. Coordinates by coordinates */
    template<typename T> inline Vec2<T> operator*(Vec2<T> V1, const Vec2<T> V2) { V1 *= V2; return V1; }

    /** Division operator. Coordinates by coordinates */
    template<typename T> inline Vec2<T> operator/(Vec2<T> V1, const Vec2<T> V2) { V1 /= V2; return V1; }

    /** Scalar addition operator. */
    template<typename T> inline Vec2<T> operator+(const T a, Vec2<T> V) { V += a; return V; }

    /** Scalar addition operator. */
    template<typename T> inline Vec2<T> operator+(Vec2<T> V, const T a) { V += a; return V; }

    /** Scalar substraction operator. */
    template<typename T> inline Vec2<T> operator-(const T a, Vec2<T> V) { V -= a; return V; }

    /** Scalar substraction operator. */
    template<typename T> inline Vec2<T> operator-(Vec2<T> V, const T a) { V -= a; return V; }

    /** Scalar multiplication operator. */
    template<typename T> inline Vec2<T> operator*(const T a, Vec2<T> V) { V *= a; return V; }

    /** Scalar multiplication operator. */
    template<typename T> inline Vec2<T> operator*(Vec2<T> V, const T a) { V *= a; return V; }

    /** Scalar division operator.*/
    template<typename T> inline Vec2<T> operator/(const T a, Vec2<T> V) { V /= a; return V; }

    /** Scalar division operator.*/
    template<typename T> inline Vec2<T> operator/(Vec2<T> V, const T a) { V /= a; return V; }


    /**
     * Return the dot product U.V between two vectors.
     */
    template<typename T> inline T dotProduct(const Vec2<T> U, const Vec2<T> V)
        {
        return U.x * V.x + U.y * V.y;
        }


    /**
     * Return the cross product UxV (i.e. the determinant of the 2 row vector matrix [U V]).
     */
    template<typename T> inline T crossProduct(const Vec2<T>& U, const Vec2<T>& V)
        {
        return (U.x * V.y - U.y * V.x);
        }


    /**
     * Return the linear interpolation: V1 + alpha(V2 - V1).
     */
    template<typename T, typename Tfloat = typename DefaultFPType<T>::fptype > inline Vec2<T> lerp(Tfloat alpha, Vec2<T> V1, Vec2<T> V2)
        {
        return Vec2<T>{ (T)(V1.x + alpha * (V2.x - V1.x)),
                        (T)(V1.y + alpha * (V2.y - V1.y)) };
        }



    template<typename T> inline int Vec2<T>::leftOf(Vec2<T> LA, Vec2<T> LB) const
        {
        T x = crossProduct(LB - LA, (*this) - LB);
        return ((x < 0) ? -1 : ((x > 0) ? 1 : 0));
        }


    template<typename T> inline bool Vec2<T>::setAsIntersection(Vec2<T> LA1, Vec2<T> LA2, Vec2<T> LB1, Vec2<T> LB2)
        {
        const T a1 = LA2.y - LA1.y;
        const T b1 = LA1.x - LA2.x;
        const T a2 = LB2.y - LB1.y;
        const T b2 = LB1.x - LB2.x;
        const T delta = a1 * b2 - a2 * b1;
        if (delta == 0) { return false; }
        const T c1 = LA1.x * a1 + LA1.y * b1;
        const T c2 = LB1.x * a2 + LB1.y * b2;
        x = ((b1 == 0) ? LA1.x : ((b2 == 0) ? LB1.x : (T)((b2 * c1 - b1 * c2) / delta)));   // complicated but insures perfect clipping
        y = ((a1 == 0) ? LA1.y : ((a2 == 0) ? LB1.y : (T)((a1 * c2 - a2 * c1) / delta)));   // for horizontal and vertical lines
        return true;
        }





}

#endif

#endif

/** end of file */

