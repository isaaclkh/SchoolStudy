import 'dart:math';

import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_ui_auth/firebase_ui_auth.dart';
import 'package:flutter/material.dart';
import 'package:google_sign_in/google_sign_in.dart';
import 'package:provider/provider.dart';

import 'firebase_options.dart';
import 'package:flutter/cupertino.dart';

class MyPage extends StatefulWidget {
  const MyPage({Key? key}) : super(key: key);

  @override
  State<MyPage> createState() => _MyPageState();
}

class _MyPageState extends State<MyPage> {

  final FirebaseAuth auth = FirebaseAuth.instance;
  GoogleSignInAccount? _user;
  GoogleSignInAccount get user => _user!;
  String gotuid = '';

  String inputData() {
    final User? user = auth.currentUser;
    final uid = user?.uid;

    setState(() {
      gotuid = uid.toString();
    });

    return uid.toString();
  }



  @override
  Widget build(BuildContext context) {
    return Scaffold(
        backgroundColor: Colors.black,
        appBar: AppBar(
          backgroundColor: Colors.grey,
          leading: IconButton(
            icon: const Icon(
              Icons.arrow_back,
              semanticLabel: 'profile',
            ),
            onPressed: () {
              Navigator.pop(context);
            },
          ),
          actions: <Widget>[
            IconButton(
              icon: const Icon(
                Icons.logout,
                semanticLabel: 'add product',
              ),
              onPressed: () {
                FirebaseAuth.instance.signOut();
                Navigator.pop(context);
              },
            ),
          ],
        ),
        body: ListView(
          children: [
            SizedBox(height: 100,),
            Container(
              width: 200,
              height: 200,
              child: Image.network(
                _user == null?
                'https://handong.edu/site/handong/res/img/logo.png' :
                user.photoUrl!,
              ),
            ),
            SizedBox(height: 50,),
            Row(children: [const SizedBox(width: 50,),Text('<$gotuid>', style: TextStyle(color: Colors.white, fontSize: 15,),),]),
            SizedBox(height: 10,),
            const Divider(
              height: 8,
              thickness: 1,
              indent: 50,
              endIndent: 50,
              color: Colors.grey,
            ),
            Row(children: [const SizedBox(width: 50,), Text(_user == null? 'Anonymous' : user.email, style: TextStyle(color: Colors.white, fontSize: 20,),),]),
            SizedBox(height: 30,),
            Row(children: [const SizedBox(width: 50,),Text('Keonho Lim', style: TextStyle(color: Colors.white, fontSize: 20,),),]),
            SizedBox(height: 10,),
            Row(children: [const SizedBox(width: 50,),Text('I promise to take the test honestly\n before GOD.', style: TextStyle(color: Colors.white, fontSize: 20,),),]),
          ],
        ),
    );
  }
}
