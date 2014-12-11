
// SDL2 Renderer for GWEN - http://www.libsdl.org/
// Added by BQ.

#include <Gwen/Gwen.h>
#include <Gwen/BaseRender.h>
#include <Gwen/Utility.h>
#include <Gwen/Font.h>
#include <Gwen/Texture.h>
#include "gwen/SDL2Renderer.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <locale>
#include <codecvt>

namespace Gwen
{
    namespace Renderer
    {

        SDL2Renderer::SDL2Renderer(SDL_Window *window)
        :   m_window(window)
        ,   m_renderer(NULL)
        {
            m_renderer = SDL_CreateRenderer(m_window, -1,
                                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        }

        SDL2Renderer::~SDL2Renderer()
        {
            SDL_DestroyRenderer(m_renderer);
        }

        void SDL2Renderer::SetDrawColor(Gwen::Color color)
        {
            m_color.r = color.r;
            m_color.g = color.g;
            m_color.b = color.b;
            m_color.a = color.a;
            
            SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
        }

        void SDL2Renderer::LoadFont(Gwen::Font* font)
        {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;

            font->realsize = font->size*Scale();
            std::string fontFile(myconv.to_bytes(font->facename));

            if (fontFile.find(".ttf") == std::string::npos)
                fontFile += ".ttf";

            TTF_Font *tfont = TTF_OpenFont(fontFile.c_str(), font->realsize);
            if (!tfont)
            {
                printf("Font load error: %s\n", TTF_GetError());
            }            
            
            font->data = tfont;
        }

        void SDL2Renderer::FreeFont(Gwen::Font* pFont)
        {
            if (pFont->data)
            {
                TTF_CloseFont(static_cast<TTF_Font*>(pFont->data));
                pFont->data = NULL;
            }
        }

        void SDL2Renderer::RenderText(Gwen::Font* pFont, Gwen::Point pos, const Gwen::String& text)
        {
            TTF_Font *tfont = static_cast<TTF_Font*>(pFont->data);
            Translate(pos.x, pos.y);
            
            SDL_Surface *surf = TTF_RenderUTF8_Blended(tfont, text.c_str(), m_color);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surf);
            SDL_FreeSurface(surf);
            
            int w, h;
            SDL_QueryTexture(texture, NULL, NULL, &w, &h);
            const SDL_Rect dest = { pos.x,pos.y, w,h };
            
            SDL_RenderCopy(m_renderer, texture, NULL, &dest);
            
            SDL_DestroyTexture(texture);
        }

        Gwen::Point SDL2Renderer::MeasureText(Gwen::Font* pFont, const Gwen::String& text)
        {
            TTF_Font *tfont = static_cast<TTF_Font*>(pFont->data);

            // If the font doesn't exist, or the font size should be changed.
            if (!tfont || pFont->realsize != pFont->size*Scale())
            {
                FreeFont(pFont);
                LoadFont(pFont);
                tfont = static_cast<TTF_Font*>(pFont->data);
            }

            if (!tfont)
                return Gwen::Point(0, 0);

            int w,h;
            TTF_SizeUTF8(tfont, text.c_str(), &w,&h);
            
            return Point(w,h);
        }

        void SDL2Renderer::StartClip()
        {
            const Gwen::Rect &rect = ClipRegion();
            const SDL_Rect clip = { rect.x,rect.y, rect.w,rect.h };
            SDL_RenderSetClipRect(m_renderer, &clip);
        }

        void SDL2Renderer::EndClip()
        {
            SDL_RenderSetClipRect(m_renderer, NULL);
        }

        void SDL2Renderer::LoadTexture(Gwen::Texture* pTexture)
        {
            if (!pTexture)
                return;

            if (pTexture->data)
                FreeTexture(pTexture);
            
            SDL_Texture *tex = NULL;
            // Don't need to read. Just load straight into render format.
            tex = IMG_LoadTexture(m_renderer, pTexture->name.c_str());

            if (tex)
            {
                int w, h;
                SDL_QueryTexture(tex, NULL, NULL, &w, &h);
                
                pTexture->data = tex;
                pTexture->width = w;
                pTexture->height = h;
                pTexture->failed = false;
            }
            else
            {
                pTexture->data = NULL;
                pTexture->failed = true;
            }
        }

        void SDL2Renderer::FreeTexture(Gwen::Texture* pTexture)
        {
            SDL_DestroyTexture(static_cast<SDL_Texture*>(pTexture->data));
            pTexture->data = NULL;
        }

        void SDL2Renderer::DrawTexturedRect(Gwen::Texture* pTexture, Gwen::Rect rect,
                                    float u1, float v1, float u2, float v2)
        {
            SDL_Texture *tex = static_cast<SDL_Texture*>(pTexture->data);

            if (!tex)
                return DrawMissingImage(rect);

            Translate(rect);
            
            const unsigned int w = pTexture->width;
            const unsigned int h = pTexture->height;
            
            const SDL_Rect source = { int(u1*w), int(v1*h), int((u2-u1)*w), int((v2-v1)*h) },
                             dest = { rect.x, rect.y, rect.w, rect.h };

            SDL_RenderCopy(m_renderer, tex, &source, &dest);
        }

        Gwen::Color SDL2Renderer::PixelColour(Gwen::Texture* pTexture, unsigned int x, unsigned int y,
                                      const Gwen::Color& col_default)
        {
            return Gwen::Color(0, 0, 0, 0);
        }

        void SDL2Renderer::DrawFilledRect(Gwen::Rect rect)
        {
            Translate(rect);
            
            const SDL_Rect srect = { rect.x, rect.y, rect.w, rect.h };
            SDL_RenderFillRect(m_renderer, &srect);
        }

        void SDL2Renderer::DrawLinedRect(Gwen::Rect rect)
        {
            Translate(rect);
            
            const SDL_Rect srect = { rect.x, rect.y, rect.w, rect.h };
            SDL_RenderDrawRect(m_renderer, &srect);
        }

        bool SDL2Renderer::BeginContext(Gwen::WindowProvider* )
        {
            SDL_RenderClear(m_renderer);
            SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
            return true;
        }

        bool SDL2Renderer::EndContext(Gwen::WindowProvider* pWindow)
        {
            return true;
        }

        bool SDL2Renderer::PresentContext(Gwen::WindowProvider* pWindow)
        {
            SDL_RenderPresent(m_renderer);
            return true;
        }

        
    } // Renderer
} // Gwen
