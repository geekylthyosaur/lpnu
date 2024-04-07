import 'package:firebase_auth/firebase_auth.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:google_sign_in/google_sign_in.dart';
import 'package:http/http.dart';
import 'package:http/io_client.dart';
import 'package:lab/firebase_options.dart';

class Auth {
  static late final FirebaseApp _app;
  static late final FirebaseAuth _auth;
  static Map<String, String>? _authHeaders;

  static init() async {
    _app = await Firebase.initializeApp(
        options: DefaultFirebaseOptions.currentPlatform);
    _auth = FirebaseAuth.instanceFor(app: _app);
  }

  static Future<void> signInWithGoogle() async {
    final GoogleSignInAccount? googleUser = await GoogleSignIn(scopes: [
      "email",
      "https://www.googleapis.com/auth/userinfo.profile",
      "https://www.googleapis.com/auth/calendar"
    ]).signIn();

    final GoogleSignInAuthentication? googleAuth =
        await googleUser?.authentication;
    _authHeaders = await googleUser?.authHeaders;

    final credential = GoogleAuthProvider.credential(
      accessToken: googleAuth?.accessToken,
      idToken: googleAuth?.idToken,
    );

    await FirebaseAuth.instance.signInWithCredential(credential);
  }

  static Future<void> signOutFromGoogle() async {
    await FirebaseAuth.instance.signOut();
  }

  static get isLoggedIn {
    return _auth.currentUser != null;
  }

  static Widget get userIcon {
    return isLoggedIn
        ? ClipOval(
            child: Image.network(
              _auth.currentUser!.photoURL.toString(),
              height: 35,
              width: 35,
              fit: BoxFit.cover,
            ),
          )
        : const ClipOval(
            child: Icon(Icons.person, size: 25),
          );
  }

  static String? get userName {
    return _auth.currentUser?.displayName;
  }

  static get authHeaders {
    return _authHeaders;
  }
}

class HttpClient extends IOClient {
  HttpClient() : super();

  @override
  Future<IOStreamedResponse> send(BaseRequest request) {
    final headers = Auth.authHeaders;
    return super.send(request..headers.addAll(headers!));
  }

  @override
  Future<Response> head(Uri url, {Map<String, String>? headers}) {
    final headers = Auth.authHeaders;
    return super.head(url, headers: headers?..addAll(headers!));
  }
}
