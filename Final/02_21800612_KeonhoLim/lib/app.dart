import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';

import 'home.dart';
import 'login.dart';
import 'add.dart';
import 'mypage.dart';

// TODO: Convert ShrineApp to stateful widget (104)
class ShrineApp extends StatelessWidget {
  const ShrineApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        body: StreamBuilder(
          stream: FirebaseAuth.instance.authStateChanges(),
          builder: (BuildContext context, AsyncSnapshot<User?> snapshot) {
            if (!snapshot.hasData) {
              return const LoginPage();
            }else{
              return const HomePage();
            }
          },
        ),
      ),
      routes: {
        '/add': (BuildContext context) => AddPage(),
        '/mypage': (BuildContext context) => MyPage(),
      },
    );
  }
}
