<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Validator;
use App\Models\Student;

class Index extends Controller
{
    public function index()
    {
        return view('index');
    }

    public function students()
    {
        $students = Student::all();
        return response()->json([
            'students' => $students,
        ]);
    }

    public function edit(Request $request, $id) 
    {
        $validator = Validator::make($request->all(), [
            'group' => 'required|string|max:255',
            'first_name' => 'required|string|max:255',
            'last_name' => 'required|string|max:255',
            'gender' => 'required|string|in:Male,Female,Other',
            'birthday' => 'required|date',
        ]);

        if ($validator->fails()) {
            return response()->json([
                'success' => false,
                'errors' => $validator->errors()->all(),
            ], 400);
        }

        $student = Student::find($id);
        if (!$student) {
            return response()->json(['message' => 'Student not found.'], 404);
        }
        
        $student->first_name = $request->input('first_name');
        $student->last_name = $request->input('last_name');
        $student->ggg = $request->input('group');
        $student->status = $request->input('status');
        $student->gender = $request->input('gender');
        $student->birthday = $request->input('birthday');
        
        $student->save();
        
        return response()->json(['message' => 'Student updated successfully.'], 200);
    }

    public function delete($id) 
    {
        $student = Student::find($id);

        if (!$student) {
            return response()->json(['message' => 'Student not found.'], 404);
        }

        $student->delete();

        return response()->json(['message' => 'Student deleted successfully.'], 200);
    }

    public function add(Request $request) 
    {
        $validator = Validator::make($request->all(), [
            'group' => 'required|string|max:255',
            'first_name' => 'required|string|max:255',
            'last_name' => 'required|string|max:255',
            'gender' => 'required|string|in:Male,Female,Other',
            'birthday' => 'required|date',
        ]);

        if ($validator->fails()) {
            return response()->json([
                'success' => false,
                'errors' => $validator->errors()->all(),
            ], 400);
        }

        try {
            $student = new Student();
            $student->id = $request->id;
            $student->ggg = $request->group;
            $student->first_name = $request->first_name;
            $student->last_name = $request->last_name;
            $student->gender = $request->gender;
            $student->birthday = $request->birthday;
            $student->status = 1;
            $student->save();
        } catch (\Exception $e) {
            return response()->json([
                'success' => false,
                'errors' => [$e->getMessage()],
            ], 400);
        }

        return response()->json([
            'success' => true,
            'student' => $student,
        ]);
    }
}
