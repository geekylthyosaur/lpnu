<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;

class Login extends Controller
{
    public function loginForm() 
    {
        return view('login');
    }

    public function login(Request $request)
    {
        $credentials = $request->only('username', 'password');

        if ($credentials['username'] == 'username' && $credentials['password'] == 'password') {
            Auth::loginUsingId(1);
            return redirect()->intended('/');
        } else {
            return redirect()->back()->withErrors(['Invalid username or password']);
        }
    }

    public function logout()
    {
        Auth::logout();
        return redirect('/');
    }
}
