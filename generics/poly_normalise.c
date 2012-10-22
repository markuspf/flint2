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

    Copyright (C) 2012 Fredrik Johansson

******************************************************************************/

#include "generics.h"

void
_elem_poly_normalise(elem_poly_struct * poly, const ring_t poly_ring)
{
    long i, size = RING_PARENT(poly_ring)->size;
    elem_ptr ptr = poly->coeffs;

    for (i = poly->length - 1;
        (i >= 0) && elem_is_zero(INDEX(ptr, i, size), poly_ring->parent); i--);

    poly->length = i + 1;
}