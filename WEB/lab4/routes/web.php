<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\Index;
use App\Http\Controllers\Login;

Route::get('/', [Index::class, 'index']);
Route::get('/students', [Index::class, 'students']);
Route::post('/students', [Index::class, 'add']);
Route::delete('/students/{id}', [Index::class, 'delete']);
Route::put('/students/{id}', [Index::class, 'edit']);

Route::get('/login', [Login::class, 'loginForm']);
Route::post('/login', [Login::class, 'login']);
Route::post('/logout', [Login::class, 'logout']);
