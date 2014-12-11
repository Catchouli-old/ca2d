/*
 *  GWEN
 *  Copyright (c) 2011 Facepunch Studios
 *  See license in Gwen.h
 */

#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/BaseRender.h"

#include <SDL2/SDL.h>

#include <locale>
#include <codecvt>

namespace Gwen
{
    namespace Renderer
    {
        class SDL2CTT;
        
        class SDL2Renderer : public Gwen::Renderer::Base
        {
        public:

            SDL2Renderer(SDL_Window *window);
            ~SDL2Renderer();

            virtual void SetDrawColor(Gwen::Color color) override;

            virtual void DrawFilledRect(Gwen::Rect rect) override;

            virtual void LoadFont(Gwen::Font* pFont) override;
            virtual void FreeFont(Gwen::Font* pFont) override;
            virtual void RenderText(Gwen::Font* pFont, Gwen::Point pos,
                                    const Gwen::String& text) override;
            virtual Gwen::Point MeasureText(Gwen::Font* pFont, const Gwen::String& text) override;

            void StartClip() override;
            void EndClip() override;

            void DrawTexturedRect(Gwen::Texture* pTexture, Gwen::Rect pTargetRect,
                                  float u1 = 0.0f, float v1 = 0.0f,
                                  float u2 = 1.0f, float v2 = 1.0f) override;
            void        LoadTexture(Gwen::Texture* pTexture) override;
            void        FreeTexture(Gwen::Texture* pTexture) override;
            Gwen::Color PixelColour(Gwen::Texture* pTexture, unsigned int x, unsigned int y,
                                    const Gwen::Color& col_default) override;

            void DrawLinedRect(Gwen::Rect rect) override;

            bool BeginContext(Gwen::WindowProvider* pWindow) override;
            bool EndContext(Gwen::WindowProvider* pWindow) override;
            bool PresentContext(Gwen::WindowProvider* pWindow) override;

        protected:

            SDL_Window      *m_window;
            SDL_Renderer    *m_renderer;
            SDL_Color        m_color;
        };


    }
}