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
import 'package:intl/intl.dart';
import 'package:url_launcher/url_launcher.dart';

import 'model/hotel.dart';
import 'model/hotel_repository.dart';
import 'supplemental/hotel_card.dart';

final Uri _url = Uri.parse('https://www.handong.edu/');


const List<Widget> togglebut = <Widget>[
  Icon(Icons.list, size: 20,),
  Icon(Icons.view_column, size: 20,),
];

class HomePage extends StatefulWidget{
  const HomePage({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() => _HomePage();
}

class _HomePage extends State<HomePage> {
  final List<bool> _isSelected = <bool>[false, true];
  ViewType _viewType = ViewType.grid;
  int _crossAxisCount = 2;
  double _aspectRatio = 0.78;

  List<Card> _buildGridCards(BuildContext context) {
    List<Hotel> hotel = HotelRepository.loadProducts(Category.all);

    if (hotel.isEmpty) {
      return const <Card>[];
    }

    final ThemeData theme = Theme.of(context);
    final NumberFormat formatter = NumberFormat.simpleCurrency(
        locale: Localizations.localeOf(context).toString());

    return hotel.map((hotel) {
      return Card(
        clipBehavior: Clip.antiAlias,
        // TODO: Adjust card heights (103)
        child: (_viewType == ViewType.list)
            ? Container(
          margin: const EdgeInsets.all(5),
          child: Row(
            children: <Widget>[
              SizedBox(
                width: 200,
                height: 100,
                child: Image.asset(
                  hotel.id,
                  fit: BoxFit.fill,
                ),
              ),
              const SizedBox(width: 5,),
              Column(
                children: <Widget>[
                  Flexible(
                    child: RichText(
                      overflow: TextOverflow.ellipsis,
                      maxLines: 1,
                      strutStyle: const StrutStyle(fontSize: 16),
                      text: TextSpan(
                        text:hotel.name,
                        style: const TextStyle(
                          color: Colors.black,
                          fontWeight: FontWeight.bold,
                          fontSize: 12,
                        ),
                      ),
                    ),
                  ),
                  const SizedBox(height: 5.0),
                  Flexible(
                    child: RichText(
                      overflow: TextOverflow.ellipsis,
                      maxLines: 2,
                      strutStyle: const StrutStyle(fontSize: 10),
                      text: TextSpan(
                        text:hotel.location,
                        style: const TextStyle(
                          color: Colors.black,
                          fontSize: 10,
                        ),
                      ),
                    ),
                  ),

                ],
              ),
            ],
          ),
        ) :
        Column(
          // TODO: Center items on the card (103)
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            AspectRatio(
              aspectRatio: 18 / 11,
              child: /*Image.asset(
                product.assetName,
                package: product.assetPackage,
                fit: BoxFit.fitWidth,
              ),*/
              Image.asset(
                hotel.id,
                fit: BoxFit.fill,
              ),
            ),
            Expanded(
              child: Padding(
                padding: const EdgeInsets.fromLTRB(7.0, 12.0, 16.0, 8.0),
                child:
                Row(
                  mainAxisSize: MainAxisSize.max,
                  children: <Widget>[
                    const Padding(
                      padding: EdgeInsets.only(right: 5,bottom: 10,),
                      child: Icon(
                        Icons.place,
                        color: Colors.blue,
                      ),
                    ),
                    SizedBox(
                      width: 120,
                      height: 100,
                      child: Column(
                        // TODO: Align labels to the bottom and center (103)
                        crossAxisAlignment: CrossAxisAlignment.start,
                        // TODO: Change innermost Column (103)
                        children: <Widget>[
                          const Icon(
                            Icons.star,
                            size: 10,
                            color: Colors.amberAccent,
                          ),
                          // TODO: Handle overflowing labels (103)
                          Flexible(
                            child: RichText(
                              overflow: TextOverflow.ellipsis,
                              maxLines: 1,
                              strutStyle: const StrutStyle(fontSize: 14),
                              text: TextSpan(
                                text:hotel.name,
                                style: const TextStyle(
                                  color: Colors.black,
                                  fontWeight: FontWeight.bold,
                                  fontSize: 12,
                                ),
                              ),
                            ),
                          ),
                          const SizedBox(height: 5.0),
                          Flexible(
                            child: RichText(
                              overflow: TextOverflow.ellipsis,
                              maxLines: 2,
                              strutStyle: const StrutStyle(fontSize: 8),
                              text: TextSpan(
                                text:hotel.location,
                                style: const TextStyle(
                                  color: Colors.black,
                                  fontSize: 10,
                                ),
                              ),
                            ),
                          ),
                          /*Container(
                            alignment: Alignment.bottomRight,
                            child: TextButton(
                              onPressed: () {

                              },
                              child: Text(
                                'more',
                                style: TextStyle(
                                  color: Colors.blue,
                                  fontSize: 10,
                                ),
                              ),

                            ),
                          ),
                          const SizedBox(height: 15.0),
                          Row(
                            children: <Widget>[
                              const Spacer(flex: 1,),
                              SizedBox(
                                width: 50,
                                height: 30,
                                child: TextButton(
                                  onPressed:(){

                                  },
                                  child: const Text(
                                    'more',
                                    style: TextStyle(
                                      color: Colors.blue,
                                      fontSize: 10,
                                    ),
                                  ),
                                ),
                              ),
                            ],
                          ),*/
                        ],
                      ),
                    ),

                  ],
                ),
              ),
            ),
          ],
        ),
      );
    }).toList();
  }

  // TODO: Add a variable for Category (104)
  @override
  Widget build(BuildContext context) {
    // TODO: Return an AsymmetricView (104)
    // TODO: Pass Category variable to AsymmetricView (104)
    return Scaffold(
      appBar: AppBar(
        title: const Text("Main"),
        centerTitle: true,
        actions: <Widget>[
          IconButton(
            icon: const Icon(
              Icons.search,
              semanticLabel: 'search',
            ),
            onPressed: () {
              Navigator.pushNamed(context, '/search');
            },
          ),
          const IconButton(
            icon: Icon(
              Icons.language,
              semanticLabel: 'filter',
            ),
            onPressed: _launchUrl,
            /*pod error
            * sudo gem install cocoapods
            * sudo gem install ffi
            * cd [project directory]
            * cd ios
            * pod install*/
          ),
        ],
      ),

      body: Column(
          children:<Widget>[
            Container(
              alignment: Alignment.topRight,
              margin: const EdgeInsets.only(top:10, right: 10),
              child:
              ToggleButtons(
                onPressed: (int index) {
                  if(index==0){
                    _crossAxisCount = 1;
                    _aspectRatio = 1;
                    _viewType = ViewType.list;
                  }
                  else{
                    _crossAxisCount = 2;
                    _aspectRatio = 0.78;
                    _viewType = ViewType.grid;
                  }
                  // Respond to button selection
                  setState(() {
                    for (int i = 0; i < _isSelected.length; i++) {
                      _isSelected[i] = i == index;
                    }
                  });

                },
                color: Colors.black.withOpacity(0.60),
                selectedColor: Colors.lightBlue,
                selectedBorderColor: Colors.lightBlue,
                fillColor: Colors.lightBlue.withOpacity(0.08),
                splashColor: Colors.lightBlue.withOpacity(0.12),
                hoverColor: Colors.lightBlue.withOpacity(0.04),
                borderRadius: BorderRadius.circular(4.0),
                isSelected: _isSelected,
                children: togglebut,

                constraints: const BoxConstraints(
                  minHeight: 40.0,
                  minWidth: 40.0,
                ),
              ),
            ),
            Expanded(
              child:
              OrientationBuilder(
                  builder: (context, orientation) {
                    return GridView.count(
                      crossAxisCount: orientation == Orientation.portrait ? _crossAxisCount : 3,
                      padding: const EdgeInsets.all(16.0),
                      childAspectRatio: _aspectRatio,
                      children: _buildGridCards(context),
                    );
                  }
              ),
            ),
          ]
      ),

      resizeToAvoidBottomInset: false,

      drawer: Drawer(
        child: ListView(
          padding: EdgeInsets.zero,
          children: [
            DrawerHeader(
              child: Stack(
                children: const [
                  Positioned(
                    bottom: 10.0,
                    left: 30.0,
                    child: Text(
                      "Pages",
                      style: TextStyle(color: Colors.white, fontSize: 28),
                    ),
                  )
                ],
              ),
              decoration: const BoxDecoration(
                color: Colors.blue,
              ),
            ),
            ListTile(
              leading: const Icon(Icons.home, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('Home'),
              onTap: () {
                Navigator.pushNamed(context, '/');
              },
            ),
            ListTile(
              leading: const Icon(Icons.search, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('Search'),
              onTap: () {
                Navigator.pushNamed(context, '/search');
              },
            ),
            ListTile(
              leading: const Icon(Icons.location_city, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('Favorite Hotel'),
              onTap: () {
                Navigator.pushNamed(context, '/list');
              },
            ),
            ListTile(
              leading: const Icon(Icons.person, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('My Page'),
              onTap: () {
                Navigator.pushNamed(context, '/go');
              },
            ),
            ListTile(
              leading: const Icon(Icons.logout, color: Colors.lightBlue,),
              contentPadding: const EdgeInsets.fromLTRB(40, 5, 5, 5),
              title: const Text('Log Out'),
              onTap: () {
                Navigator.pushNamed(context, '/login');
              },
            ),
          ],
        ),
      ),
    );
  }
}

Future<void> _launchUrl() async {
  if (!await launchUrl(_url)) {
    throw 'Could not launch $_url';
  }
}

enum ViewType { grid, list }