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
// stores ExpansionPanel state information

final filters = <String>{};

class Item {
  Item({
    required this.headerValue,
    this.isExpanded = false,
  });

  String headerValue;
  bool isExpanded;
}

List<Item> generateItems(int numberOfItems) {
  return List<Item>.generate(numberOfItems, (int index) {
    return Item(
      headerValue: 'Filter',
    );
  });
}

class SearchPage extends StatefulWidget{
  const SearchPage({Key? key, this.restorationId}) : super(key: key);
  final String? restorationId;

  @override
  State<SearchPage> createState() => _SearchPage();
}

class _SearchPage extends State<SearchPage> with RestorationMixin{
  final List<Item> _data = generateItems(1);
  @override
  String? get restorationId => widget.restorationId;
  late String selectedDate = "Not selected.";
  late String selectedFilters = "Not selected.";

  final RestorableDateTime _selectedDate =
  RestorableDateTime(DateTime.now());
  late final RestorableRouteFuture<DateTime?> _restorableDatePickerRouteFuture =
  RestorableRouteFuture<DateTime?>(
    onComplete: _selectDate,
    onPresent: (NavigatorState navigator, Object? arguments) {
      return navigator.restorablePush(
        _datePickerRoute,
        arguments: _selectedDate.value.millisecondsSinceEpoch,
      );
    },
  );

  static Route<DateTime> _datePickerRoute(
      BuildContext context,
      Object? arguments,
      ) {
    return DialogRoute<DateTime>(
      context: context,
      builder: (BuildContext context) {
        return DatePickerDialog(
          restorationId: 'date_picker_dialog',
          initialEntryMode: DatePickerEntryMode.calendarOnly,
          initialDate: DateTime.fromMillisecondsSinceEpoch(arguments! as int),
          firstDate: DateTime(2022),
          lastDate: DateTime(2030),
        );
      },
    );
  }

  @override
  void restoreState(RestorationBucket? oldBucket, bool initialRestore) {
    registerForRestoration(_selectedDate, 'selected_date');
    registerForRestoration(
        _restorableDatePickerRouteFuture, 'date_picker_route_future');
  }

  void _selectDate(DateTime? newSelectedDate) {
    if (newSelectedDate != null) {
      setState(() {
        _selectedDate.value = newSelectedDate;
        String dateFormat = DateFormat('yyyy.MMM.d (EE)').format(newSelectedDate);
        selectedDate = dateFormat;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Search'),
        centerTitle: true,
      ),
      body: Column(
        children: <Widget>[
          Expanded(
              child: ListView(
                children: <Widget>[
                  SingleChildScrollView(
                      child: Container(
                        child: _buildPanel(),
                      ),
                    ),
                   Column(
                     crossAxisAlignment: CrossAxisAlignment.start,
                     children: <Widget>[
                       Container(
                         margin: const EdgeInsets.only(left: 16, top: 50,),
                         child: const Text('Date', style: TextStyle(fontWeight: FontWeight.bold, fontSize: 16),),
                       ),
                       Row(
                         children: <Widget>[
                           Expanded(
                             child: Column(
                               crossAxisAlignment: CrossAxisAlignment.start,
                               children: <Widget>[
                                 Container(
                                   padding: const EdgeInsets.only(left: 30, top: 30,),
                                   child: const Text('\u{1F4C5}check-in',),
                                 ),
                                 Container(
                                   padding: const EdgeInsets.only(left: 30,),
                                   child: Text(selectedDate, style: const TextStyle(fontWeight: FontWeight.w300, fontSize: 10, color: Colors.grey,),),
                                 ),
                               ],
                             ),
                           ),
                           Container(
                             margin: EdgeInsets.only(right: 10,),
                             child: OutlinedButton(
                               onPressed: () {
                                 _restorableDatePickerRouteFuture.present();
                               },
                               style: ButtonStyle(
                                 backgroundColor: MaterialStateProperty.resolveWith<Color>((states) {
                                  return Colors.lightBlueAccent;},),
                               ),
                               child: const Text('Open Date Picker', style: TextStyle(color: Colors.black,),),
                             ),
                           ),
                         ],
                       ),
                     ],
                   ),
              ],
            ),
          ),

          Align(
            alignment: Alignment.bottomCenter,
            child: Container(
              margin: EdgeInsets.only(bottom: 20),
              child:
              ElevatedButton(
                style: ElevatedButton.styleFrom(
                  padding: const EdgeInsets.symmetric(horizontal: 50, vertical: 15),
                  elevation: 5,
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(10),
                  )
                ),
                onPressed: () => showDialog(
                    context: context,
                    builder: (BuildContext context) => AlertDialog(
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(0),
                      ),
                      title: Container(
                        child: const Center(
                          child: Text(
                            'Please check\nyour choice :)',
                            textAlign: TextAlign.center,
                            style: TextStyle(
                              color: Colors.white,
                            ),
                          ),
                        ),
                        height: 100,
                        decoration: const BoxDecoration(
                          color: Colors.blue,
                        ),
                      ),
                      titlePadding: const EdgeInsets.all(0),
                      content:
                      Column(
                        mainAxisSize: MainAxisSize.min,
                        children: <Widget>[
                          Row(
                            children: <Widget>[
                              const Icon(
                                Icons.wifi,
                                size: 20,
                                color: Colors.lightBlue,
                              ),
                              const SizedBox(width: 10,),
                              Flexible(
                                child: Text(
                                  selectedFilters = filters.map((e){
                                    return e;
                                  }).toString(),
                                  overflow: TextOverflow.ellipsis,
                                  maxLines: 2,
                                  style: const TextStyle(
                                    color: Colors.grey,
                                  ),
                                ),
                              ),
                            ],
                          ),
                          const SizedBox(height: 15,),
                          Row(
                            children: <Widget>[
                              const Icon(
                                Icons.calendar_month,
                                size: 20,
                                color: Colors.lightBlue,
                              ),
                              const SizedBox(width: 10,),
                              const Text(
                                "IN",
                                textAlign: TextAlign.center,
                                style: TextStyle(
                                  fontWeight: FontWeight.bold,
                                ),
                              ),
                              const SizedBox(width: 10,),
                              Text(
                                selectedDate,
                                textAlign: TextAlign.center,
                                style: const TextStyle(
                                  color: Colors.grey,
                                ),
                              ),
                            ],
                          ),
                        ],
                      ),
                      actions: <Widget>[
                        Row(
                          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                          children: <Widget>[
                            ElevatedButton(
                              style: ElevatedButton.styleFrom(
                                shape: RoundedRectangleBorder(
                                  borderRadius: BorderRadius.circular(10),
                                ),
                              ),
                              onPressed: () => Navigator.pop(context, 'Search'),
                              child: const Text('Search'),
                            ),
                            ElevatedButton(
                              style: ElevatedButton.styleFrom(
                                  primary: Colors.grey[350],
                                  shape: RoundedRectangleBorder(
                                    borderRadius: BorderRadius.circular(10),
                                  ),
                              ),
                              onPressed: () => Navigator.pop(context, 'Cancel'),
                              child: const Text('Cancel'),
                            ),
                          ],
                        ),
                      ],
                    ),
                ),
                child: const Text('Search', style: TextStyle(fontSize: 20),),
              ),
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildPanel() {
    return ExpansionPanelList(
      elevation: 1,
      expansionCallback: (int index, bool isExpanded) {
        setState(() {
          _data[index].isExpanded = !isExpanded;
        });
      },
      children: _data.map<ExpansionPanel>((Item item) {
        return ExpansionPanel(
          headerBuilder: (BuildContext context, bool isExpanded) {
            return
              ListTile(
                title: Row(
                  children: const <Widget>[
                    Text('Filter', style: TextStyle(fontWeight: FontWeight.bold),),
                    Spacer(flex: 3,),
                    Text('select filters',),
                    Spacer(flex: 2,),
                  ],
                )
              );
          },
          body: const Filter(),
          isExpanded: item.isExpanded,
        );
      }).toList(),
    );
  }
}

class Filter extends StatefulWidget {
  const Filter({Key? key}) : super(key: key);

  @override
  State<Filter> createState() => _Filter();
}

class _Filter extends State<Filter> {
  final List<bool> isChecked = <bool>[false,false,false];

  @override
  Widget build(BuildContext context) {
    Color getColor(Set<MaterialState> states) {
      const Set<MaterialState> interactiveStates = <MaterialState>{
        MaterialState.pressed,
        MaterialState.hovered,
        MaterialState.focused,
      };
      if (states.any(interactiveStates.contains)) {
        return Colors.blue;
      }
      return Colors.blue;
    }

    return Column(
      children: <Widget>[
        Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Checkbox(
              checkColor: Colors.white,
              fillColor: MaterialStateProperty.resolveWith(getColor),
              value: isChecked[0],
              onChanged: (bool? value) {
                setState(() {
                  isChecked[0] = value!;
                  if(isChecked[0]){
                    filters.add('No Kids Zone');
                  }
                  else{
                    filters.remove('No Kids Zone');
                  }
                });
              },
            ),
            const Text('No Kids Zone'),
          ],
        ),
        Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Checkbox(
              checkColor: Colors.white,
              fillColor: MaterialStateProperty.resolveWith(getColor),
              value: isChecked[1],
              onChanged: (bool? value) {
                setState(() {
                  isChecked[1] = value!;
                  if(isChecked[1]){
                    filters.add('Pet-Friendly');
                  }
                  else{
                    filters.remove('Pet-Friendly');
                  }
                });
              },
            ),
            const Text('Pet-Friendly'),
            const SizedBox(width: 6,),
          ],
        ),
        Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            const SizedBox(width: 10,),
            Checkbox(
              checkColor: Colors.white,
              fillColor: MaterialStateProperty.resolveWith(getColor),
              value: isChecked[2],
              onChanged: (bool? value) {
                setState(() {
                  isChecked[2] = value!;
                  if(isChecked[2]){
                    filters.add('Free breakfast');
                  }
                  else{
                    filters.remove('Free breakfast');
                  }
                });
              },
            ),
            const Text('Free breakfast'),
          ],
        ),
      ],
    );

  }
}