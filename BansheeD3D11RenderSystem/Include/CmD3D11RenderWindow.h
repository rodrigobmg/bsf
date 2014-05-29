#pragma once

#include "CmD3D11Prerequisites.h"
#include "CmRenderWindow.h"

namespace BansheeEngine
{
	class BS_D3D11_EXPORT D3D11RenderWindow : public RenderWindow
	{
	public:
		~D3D11RenderWindow();

		/**
		 * @copydoc RenderWindow::reposition
		 */
		void move(INT32 left, INT32 top);

		/**
		 * @copydoc RenderWindow::resize
		 */
		void resize(UINT32 width, UINT32 height);

		/**
		 * @copydoc RenderWindow::setHidden
		 */
		void setHidden(bool hidden);

		/**
		 * @copydoc RenderWindow::setActive
		 */
		void setActive(bool state);

		/**
		 * @copydoc RenderWindow::setFullscreen(UINT32, UINT32, float, UINT32)
		 */
		void setFullscreen(UINT32 width, UINT32 height, float refreshRate = 60.0f, UINT32 monitorIdx = 0);

		/**
		 * @copydoc RenderWindow::setFullscreen(const VideoMode&)
		 */
		void setFullscreen(const VideoMode& mode);

		/**
		* @copydoc RenderWindow::setWindowed
		*/
		void setWindowed(UINT32 width, UINT32 height);

		/**
		 * @copydoc RenderWindow::copyContentsToMemory
		 */
		void copyToMemory(const PixelData &dst, FrameBuffer buffer);

		/**
		 * @copydoc RenderWindow::swapBuffers
		 */
		void swapBuffers();

		/**
		 * @copydoc RenderWindow::isClosed
		 */
		bool isClosed() const { return mClosed; }

		/**
		 * @copydoc RenderWindow::isHidden
		 */
		bool isHidden() const { return mHidden; }

		/**
		 * @copydoc RenderWindow::screenToWindowPos
		 */
		Vector2I screenToWindowPos(const Vector2I& screenPos) const;

		/**
		 * @copydoc RenderWindow::windowToScreenPos
		 */
		Vector2I windowToScreenPos(const Vector2I& windowPos) const;

		/**
		 * @copydoc RenderWindow::getCustomAttribute
		 */
		void getCustomAttribute(const String& name, void* pData) const;

		/**
		 * @copydoc RenderWindow::requiresTextureFlipping
		 */
		bool requiresTextureFlipping() const { return false; }

		void _windowMovedOrResized();

		DXGI_SWAP_CHAIN_DESC* _getPresentationParameters() { return &mSwapChainDesc; }
		HWND _getWindowHandle() const { return mHWnd; }

	protected:
		friend class D3D11RenderWindowManager;
		D3D11RenderWindow(const RENDER_WINDOW_DESC& desc, D3D11Device& device, IDXGIFactory* DXGIFactory);

		void createSizeDependedD3DResources();
		void destroySizeDependedD3DResources();

		IDXGIDevice* queryDxgiDevice(); 

		bool checkMultiSampleQuality(UINT32 SampleCount, UINT32 *outQuality, DXGI_FORMAT format);

		void createSwapChain();
		void resizeSwapChainBuffers(UINT32 width, UINT32 height);
		
		/**
		 * @copydoc RenderWindow::initialize_internal().
		 */
		void initialize_internal();

		/**
		 * @copydoc RenderWindow::destroy_internal().
		 */
		void destroy_internal();
	protected:
		D3D11Device& mDevice;
		IDXGIFactory* mDXGIFactory;
		bool mIsExternal;
		bool mSizing;
		bool mClosed;
		bool mIsChild;

		DXGI_SAMPLE_DESC mMultisampleType;
		bool mVSync;
		UINT32 mVSyncInterval;
		UINT32 mRefreshRateNumerator;
		UINT32 mRefreshRateDenominator;

		ID3D11Texture2D* mBackBuffer;
		ID3D11RenderTargetView*	mRenderTargetView;
		TextureViewPtr mDepthStencilView;
		TexturePtr mDepthStencilBuffer;

		IDXGISwapChain*	mSwapChain;
		DXGI_SWAP_CHAIN_DESC mSwapChainDesc;

		HWND mHWnd;
	};
}