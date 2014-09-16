// Copyright � 2010-2014 The CefSharp Project. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found in the LICENSE file.
#pragma once

#include "Stdafx.h"
#include "include/cef_v8.h"

#include "JavascriptMethodHandler.h"

using namespace CefSharp::Internals;
using namespace System::Runtime::Serialization;

namespace CefSharp
{
    public ref class JavascriptMethodWrapper
    {
    private:
        MCefRefPtr<JavascriptMethodHandler> _javascriptMethodHandler;
        JavascriptMethod^ _javascriptMethod;
        int64 _ownerId;
        Func<IBrowserProcess^>^ _createBrowserProxyDelegate;

    internal:
        MCefRefPtr<CefV8Value> V8Value;

    public:
        JavascriptMethodWrapper(JavascriptMethod^ javascriptMethod, int64 ownerId, Func<IBrowserProcess^>^ createBrowserProxyDelegate)
        {
            _javascriptMethod = javascriptMethod;
            _ownerId = ownerId;
            _createBrowserProxyDelegate = createBrowserProxyDelegate;
            _javascriptMethodHandler = new JavascriptMethodHandler(gcnew Func<array<Object^>^, BrowserProcessResponse^>(this, &JavascriptMethodWrapper::Execute));
        }

        void Bind();
        BrowserProcessResponse^ Execute(array<Object^>^ parameters);
    };
}