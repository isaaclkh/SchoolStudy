import 'dart:math';

import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_ui_auth/firebase_ui_auth.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

import 'app.dart';
import 'firebase_options.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  runApp(ChangeNotifierProvider(
      create: (context) => ApplicationState(),
      builder: ((context, child) => ShrineApp()),
  ));
}

class ApplicationState extends ChangeNotifier {
  ApplicationState() {
    init();
  }

  bool _loggedIn = false;
  bool get loggedIn => _loggedIn;

  Future<void> init() async {

    FirebaseAuth.instance.userChanges().listen((user) {
      if (user != null) {
        _loggedIn = true;
      } else {
        _loggedIn = false;
      }
      notifyListeners();
    });


  }

  Future<void> addProduct(String name, String price, String discript, String imageurl) {

    return FirebaseFirestore.instance
        .collection('product')
        .doc(name)
        .set(<String, dynamic>{
      'name': name,
      'price': price,
      'discript': discript,
      'imageurl': imageurl,
      'timestamp': DateTime.now().millisecondsSinceEpoch, // When created and last modified
      'userId': FirebaseAuth.instance.currentUser!.uid,
    });

  }
}