/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2016 Vincent Delecroix

******************************************************************************/

#include <gmp.h>
#include "flint.h"
#include "nmod_vec.h"
#include "nmod_poly.h"

void
_nmod_poly_power_sums_to_poly_naive(mp_ptr res, mp_srcptr poly, slong len,
                                    nmod_t mod)
{
    slong i, k;
    slong d = poly[0];

    res[d] = 1;
    for (k = 1; k < FLINT_MIN(d + 1, len); k++)
    {
        res[d - k] = poly[k];
        for (i = 1; i < k; i++)
            res[d - k] = nmod_add(res[d - k],
                    nmod_mul(res[d - k + i], poly[i], mod),
                    mod);
        res[d - k] = nmod_div(res[d - k], k, mod);
        res[d - k] = nmod_neg(res[d - k], mod);
    }
    for (k = len; k <= d; k++)
    {
        res[d - k] = 0;
        for (i = 1; i < len; i++)
            res[d - k] = nmod_add(res[d - k],
                    nmod_mul(res[d - k + i], poly[i], mod),
                    mod);
        res[d - k] = nmod_div(res[d - k], k, mod);
        res[d - k] = nmod_neg(res[d - k], mod);
    }
}

void
nmod_poly_power_sums_to_poly_naive(nmod_poly_t res, const nmod_poly_t Q)
{
    if (Q->length == 0)
    {
        nmod_poly_fit_length(res, 1);
        res->coeffs[0] = 1;
        _nmod_poly_set_length(res, 1);
    }
    else
    {
        slong d = Q->coeffs[0];
        if (Q == res)
        {
            nmod_poly_t t;
            nmod_poly_init_preinv(t, Q->mod.n, Q->mod.ninv);
            nmod_poly_fit_length(t, d + 1);
            _nmod_poly_power_sums_to_poly_naive(t->coeffs, Q->coeffs,
                                                Q->length, Q->mod);
            nmod_poly_swap(res, t);
            nmod_poly_clear(t);
        }
        else
        {
            nmod_poly_fit_length(res, d + 1);
            _nmod_poly_power_sums_to_poly_naive(res->coeffs, Q->coeffs,
                                                Q->length, Q->mod);
        }
        _nmod_poly_set_length(res, d + 1);
        _nmod_poly_normalise(res);
    }
}
