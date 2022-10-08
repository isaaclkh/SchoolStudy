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
import 'package:lottie/lottie.dart';
import 'package:intl/intl.dart';

import 'model/hotel.dart';
import 'model/hotel_repository.dart';
import 'detail.dart';

class MyPage extends StatefulWidget{
  const MyPage({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() => _MyPage();

}

class _MyPage extends State<MyPage> {
  bool empty = false;

  List<Card> _buildGridCards(BuildContext context) {

    if (saving.isEmpty) {
      empty = true;
    }

    return saving.map((hotel) {
      if(empty){
        <Card>[];
      }
      return Card(
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(50),
        ),
        child: ClipRRect(
          borderRadius: BorderRadius.circular(50),
          child: Image.asset(
              hotel.id,
              fit: BoxFit.fill,
          ),
        ),
      );
    }).toList();
  }


  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('My Page'),
        centerTitle: true,
      ),
      body: ListView(
        children: <Widget>[
          const SizedBox(height: 30,),
          Column(
            crossAxisAlignment: CrossAxisAlignment.center,
            children: <Widget>[
              Container(
                height: 200,
                width: 200,
                decoration: const BoxDecoration(
                  borderRadius: BorderRadius.all(Radius.circular(100)),
                ),
                child: ClipOval(
                  child: Lottie.asset('assets/coding.json', fit: BoxFit.cover),
                ),
              ),
              const SizedBox(height: 5,),
              const Text(
                'Keonho Lim',
                style: TextStyle(
                  fontSize:15,
                  fontWeight: FontWeight.bold,
                ),
              ),
              const Text(
                '21800612',
                style: TextStyle(
                  fontSize:15,
                  color: Colors.grey,
                ),
              ),
              Container(
                margin: const EdgeInsets.only(left: 20, top: 40,),
                alignment: Alignment.centerLeft,
                child: const Text(
                  'My Favorite Hotel List',
                  style: TextStyle(
                    fontSize:20,
                    fontWeight: FontWeight.bold,
                  ),
                ),
              ),
              const SizedBox(height: 10,),
            ],
          ),
          SizedBox(
            //height: saving.length * 200,
            height: 500,
            child: GridView.count(
              padding: const EdgeInsets.all(0),
              childAspectRatio: 2,
              crossAxisCount: 1,
              children: _buildGridCards(context),
              physics: NeverScrollableScrollPhysics(),
            ),
          ),
        ],
      ),
    );
  }


}
