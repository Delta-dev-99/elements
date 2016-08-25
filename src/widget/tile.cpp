/*=================================================================================================
   Copyright (c) 2016 Joel de Guzman

   Licensed under a Creative Commons Attribution-ShareAlike 4.0 International.
   http://creativecommons.org/licenses/by-sa/4.0/
=================================================================================================*/
#include <photon/widget/tile.hpp>
#include <photon/support/context.hpp>

namespace photon
{
   ////////////////////////////////////////////////////////////////////////////////////////////////
   // Vertical Tiles
   ////////////////////////////////////////////////////////////////////////////////////////////////
   rect vtile_widget::limits(basic_context const& ctx) const
   {
      rect limits{ 0.0, 0.0, full_extent, 0.0 };
      for (auto const& elem : *this)
      {
         rect  el = elem->limits(ctx);

         limits.top += el.top;
         limits.bottom += el.bottom;
         clamp_min(limits.left, el.left);
         clamp_max(limits.right, el.right);
      }

      clamp_min(limits.right, limits.left);
      return limits;
   }

   void vtile_widget::layout(context const& ctx)
   {
      _left = ctx.bounds.left;
      _right = ctx.bounds.right;

      _tiles.resize(size()+1);

      rect     limits   = this->limits(ctx);
      double   height   = ctx.bounds.height();
      double   extra    = limits.bottom - height;
      double   m_size   = limits.bottom - limits.top;
      double   curr     = ctx.bounds.top;
      auto     i        = _tiles.begin();

      for (auto const& elem : *this)
      {
         rect  limits = elem->limits(ctx);

         *i++ = curr;
         auto prev = curr;
         curr += limits.bottom;

         if ((extra != 0) && (m_size != 0))
            curr -= extra * (limits.bottom - limits.top) / m_size;

         rect ebounds = { _left, float(prev), _right, float(curr) };
         elem->layout(context{ ctx, elem.get(), ebounds });
      }
      *i = curr;
   }

   rect vtile_widget::bounds_of(context const& ctx, std::size_t index) const
   {
      return rect{ _left, _tiles[index], _right, _tiles[index+1] };
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////
   // Horizontal Tiles
   ////////////////////////////////////////////////////////////////////////////////////////////////
   rect htile_widget::limits(basic_context const& ctx) const
   {
      rect limits{ 0.0, 0.0, 0.0, full_extent };
      for (auto const& elem : *this)
      {
         rect  el = elem->limits(ctx);

         limits.left += el.left;
         limits.right += el.right;
         clamp_min(limits.top, el.top);
         clamp_max(limits.bottom, el.bottom);
      }

      clamp_min(limits.bottom, limits.top);
      return limits;
   }

   void htile_widget::layout(context const& ctx)
   {
      _top = ctx.bounds.top;
      _bottom = ctx.bounds.bottom;

      _tiles.resize(size()+1);

      rect     limits   = this->limits(ctx);
      double   width    = ctx.bounds.width();
      double   extra    = limits.right - width;
      double   m_size   = limits.right - limits.left;
      double   curr     = ctx.bounds.left;
      auto     i        = _tiles.begin();

      for (auto const& elem : *this)
      {
         rect  limits = elem->limits(ctx);

         *i++ = curr;
         auto prev = curr;
         curr += limits.right;

         if ((extra != 0) && (m_size != 0))
            curr -= extra * (limits.right - limits.left) / m_size;

         rect ebounds = { float(prev), _top, float(curr), _bottom };
         elem->layout(context{ ctx, elem.get(), ebounds });
      }
      *i = curr;
   }

   rect htile_widget::bounds_of(context const& ctx, std::size_t index) const
   {
      return rect{ _tiles[index], _top, _tiles[index + 1], _bottom };
   }
}