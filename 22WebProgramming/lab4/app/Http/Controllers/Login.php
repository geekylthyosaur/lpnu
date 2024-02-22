<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Validator;
use App\Models\User;

class Login extends Controller
{
    public function loginForm() 
    {
        return view('login');
    }

    public function login(Request $request)
    {
        $validator = Validator::make($request->all(), [
            'username' => 'required|string|max:255',
            'password' => 'required|string|max:255',
        ]);

        if ($validator->fails()) {
            return response()->json([
                'success' => false,
                'errors' => $validator->errors()->all(),
            ], 400);
        }

        $credentials = $request->only('username', 'password');

        $user = User::where('name', '=', $credentials['username'])->first();
        if (!$user) {
            return response()->json(['message' => $user], 403);
        }

        if ($credentials['password'] == $user->password) {
            Auth::loginUsingId($user->id);
        } else {
            return response()->json([
                'success' => false,
                'errors' => ['Invalid username or password'],
            ], 403);
        }
        
        return response()->json([
            'success' => true,
        ], 200);
    }

    public function id() 
    {
        if (Auth::check()) {
            return response()->json([
                'username' => Auth::user()->name,
            ]);
        } else {
            return response()->json([
                'username' => null,
            ]);
        }
    }

    public function signup(Request $request) 
    {
        $validator = Validator::make($request->all(), [
            'username' => 'required|string|max:255',
            'password' => 'required|string|max:255',
        ]);

        if ($validator->fails()) {
            return response()->json([
                'success' => false,
                'errors' => $validator->errors()->all(),
            ], 400);
        }

        try {
            $user = new User();
            $user->name = $request->username;
            $user->password = $request->password;
            $user->save();
        } catch (\Exception $e) {
            return response()->json([
                'success' => false,
                'errors' => [$e->getMessage()],
            ], 400);
        }
            Auth::loginUsingId($user->id);

        return response()->json([
            'success' => true,
            'student' => $user,
        ]);
    }

    public function logout()
    {
        Auth::logout();
    }
}
