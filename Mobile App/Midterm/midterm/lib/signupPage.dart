// Copyright 2018-present the Flutter authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import 'package:flutter/material.dart';

class SignupPage extends StatefulWidget {
  const SignupPage({Key? key}) : super(key: key);

  @override
  _SignupPage createState() => _SignupPage();
}

class _SignupPage extends State<SignupPage> {
  final _usernameController = TextEditingController();
  final _passwordController = TextEditingController();
  final _confirmController = TextEditingController();
  final _emailController = TextEditingController();

  final _formKey1 = GlobalKey<FormState>();
  final _formKey2 = GlobalKey<FormState>();
  final _formKey3 = GlobalKey<FormState>();
  final _formKey4 = GlobalKey<FormState>();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SafeArea(
        child: ListView(
          padding: const EdgeInsets.symmetric(horizontal: 24.0),
          children: <Widget>[
            const SizedBox(height: 12.0),
            Form(
              key: _formKey1,
              child:
              TextFormField(
                controller: _usernameController,
                decoration: const InputDecoration(
                  filled: true,
                  labelText: 'Username',
                ),
                // The validator receives the text that the user has entered.
                validator: (value) {
                  String patternnum = '^(.*?[0-9]){3}';
                  String patternchar = '^(.*?[A-z]){3}';
                  bool validnum = !(value!.contains(RegExp(patternnum)));
                  bool validchar = !(value.contains(RegExp(patternchar)));

                  if (value == null || value.isEmpty || validnum || validchar) {
                    return 'Username is invalid';
                  }
                  return null;
                },
              ),
            ),
            const SizedBox(height: 12.0),
            Form(
              key: _formKey2,
              child:
              TextFormField(
                controller: _passwordController,
                decoration: const InputDecoration(
                  filled: true,
                  labelText: 'Password',
                ),
                // The validator receives the text that the user has entered.
                validator: (value) {
                  if (value == null || value.isEmpty) {
                    return 'Please enter Password';
                  }
                  return null;
                },
                obscureText: true,
              ),
            ),
            const SizedBox(height: 12.0),
            Form(
              key: _formKey3,
              child:
              TextFormField(
                controller: _confirmController,
                decoration: const InputDecoration(
                  filled: true,
                  labelText: 'Confirm Password',
                ),
                // The validator receives the text that the user has entered.
                validator: (value) {

                  if (value == null || value.isEmpty) {
                    return 'Please retype password';
                  }
                  if(value != _passwordController.text){
                    return 'Confirm Password does not match Password';
                  }
                  return null;
                },
                obscureText: true,
              ),
            ),
            const SizedBox(height: 12.0),
            Form(
              key: _formKey4,
              child:
              TextFormField(
                controller: _emailController,
                decoration: const InputDecoration(
                  filled: true,
                  labelText: 'Email Address',
                ),
                // The validator receives the text that the user has entered.
                validator: (value) {
                  if (value == null || value.isEmpty) {
                    return 'Please enter Email Address';
                  }
                  return null;
                },
              ),
            ),
            OverflowBar(
              alignment: MainAxisAlignment.end,
              children: <Widget>[
                // TODO: Add a beveled rectangular border to CANCEL (103)
                // TODO: Add an elevation to NEXT (103)
                // TODO: Add a beveled rectangular border to NEXT (103)
                ElevatedButton(
                  child: const Text('SIGN UP'),
                  style: ElevatedButton.styleFrom(
                    primary: Colors.grey,
                  ),
                  onPressed: () {
                    if (_formKey1.currentState!.validate() && _formKey2.currentState!.validate() && _formKey3.currentState!.validate() && _formKey4.currentState!.validate()) {
                      // If the form is valid, display a snackbar. In the real world,
                      // you'd often call a server or save the information in a database.
                      Navigator.pop(context);
                    }
                  },
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
