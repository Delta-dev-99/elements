/*=============================================================================
   Copyright (c) 2016-2019 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_GALLERY_MESSAGE_BOX_JUNE_5_2016)
#define ELEMENTS_GALLERY_MESSAGE_BOX_JUNE_5_2016

#include <elements/element/text.hpp>
#include <elements/element//gallery/button.hpp>
#include <elements/element//gallery/dialog.hpp>

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // Message Box 0 (no button)
   ////////////////////////////////////////////////////////////////////////////
   inline auto message_box0(
      char const* message
    , std::uint32_t icon_id
    , extent text_box_size = get_theme().message_textbox_size
   )
   {
      auto textbox = fixed_size(text_box_size, static_text_box{ message });
      return dialog0(
         margin({ 20, 20, 20, 20 }, htile(
            align_top(icon{ icon_id, 2.5 }),
            left_margin(20, std::move(textbox))
         ))
      );
   }

   ////////////////////////////////////////////////////////////////////////////
   // Message Box 1 (single botton, e.g. OK)
   ////////////////////////////////////////////////////////////////////////////
   template <typename F>
   inline auto message_box1(
      view& view_
    , char const* message
    , std::uint32_t icon_id
    , F&& on_ok
    , char const* ok_text = "OK"
    , extent text_box_size = get_theme().message_textbox_size
    , color ok_color = get_theme().indicator_color
   )
   {
      auto textbox = fixed_size(text_box_size, static_text_box{ message });
      return dialog1(
         view_,
         htile(
            align_top(icon{ icon_id, 2.5 }),
            left_margin(20, std::move(textbox))
         ),
         std::forward<F>(on_ok),
         ok_text,
         ok_color
      );
   }

   ////////////////////////////////////////////////////////////////////////////
   // Message Box 2 (two bottons, e.g. Cancel and OK)
   ////////////////////////////////////////////////////////////////////////////
   template <typename F1, typename F2>
   inline auto message_box2(
      view& view_
    , char const* message
    , std::uint32_t icon_id
    , F1&& on_ok
    , F2&& on_cancel
    , char const* cancel_text = "Cancel"
    , char const* ok_text = "OK"
    , extent text_box_size = get_theme().message_textbox_size
    , color ok_color = get_theme().indicator_color
   )
   {
      auto textbox = fixed_size(text_box_size, static_text_box{ message });
      return dialog2(
         view_,
         htile(
            align_top(icon{ icon_id, 2.5 }),
            left_margin(20, std::move(textbox))
         ),
         std::forward<F1>(on_ok),
         std::forward<F2>(on_cancel),
         cancel_text,
         ok_text,
         ok_color
      );
   }
}}

#endif