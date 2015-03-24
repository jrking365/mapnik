/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2014 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef MAPNIK_GEOMETRY_TO_DS_TYPE_HPP
#define MAPNIK_GEOMETRY_TO_DS_TYPE_HPP

// mapnik
#include <mapnik/global.hpp>
#include <mapnik/geometry_impl.hpp>
#include <mapnik/datasource_geometry_type.hpp>
#include <mapnik/util/variant.hpp>
// boost
#include <boost/optional.hpp>

namespace mapnik { namespace util {

namespace detail {

struct datasource_geometry_type
{
    mapnik::datasource_geometry_t operator () (mapnik::new_geometry::geometry_empty const&) const
    {
        return mapnik::datasource_geometry_t::Unknown;
    }

    mapnik::datasource_geometry_t operator () (mapnik::new_geometry::point const&) const
    {
        return mapnik::datasource_geometry_t::Point;
    }

    mapnik::datasource_geometry_t operator () (mapnik::new_geometry::line_string const&) const
    {
        return mapnik::datasource_geometry_t::LineString;
    }

    mapnik::datasource_geometry_t operator () (mapnik::new_geometry::polygon const&) const
    {
        return mapnik::datasource_geometry_t::Polygon;
    }

    mapnik::datasource_geometry_t operator () (mapnik::new_geometry::multi_point const&) const
    {
        return mapnik::datasource_geometry_t::Point;
    }

    mapnik::datasource_geometry_t operator () (mapnik::new_geometry::multi_line_string const&) const
    {
        return mapnik::datasource_geometry_t::LineString;
    }

    mapnik::datasource_geometry_t operator () (mapnik::new_geometry::multi_polygon const&) const
    {
        return mapnik::datasource_geometry_t::Polygon;
    }

    mapnik::datasource_geometry_t operator () (mapnik::new_geometry::geometry_collection const&) const
    {
        return mapnik::datasource_geometry_t::Collection;
    }
};
} // detail

static inline mapnik::datasource_geometry_t to_ds_type(mapnik::new_geometry::geometry const& geom)
{
    return util::apply_visitor(detail::datasource_geometry_type(), geom);
}

}}


#endif // MAPNIK_GEOMETRY_TO_DS_TYPE_HPP
