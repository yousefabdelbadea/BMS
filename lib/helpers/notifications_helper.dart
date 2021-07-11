import 'package:flutter/foundation.dart';
import 'package:flutter_local_notifications/flutter_local_notifications.dart';

// Test are only possible during integration test on a real device

class ReceivedNotification {
  final int id;
  final String title;
  final String body;
  final String payload;

  ReceivedNotification(
      {@required this.id,
      @required this.title,
      @required this.body,
      @required this.payload});
}

class LocalNotification {
  FlutterLocalNotificationsPlugin flutterLocalNotificationsPlugin =
      FlutterLocalNotificationsPlugin();
  AndroidInitializationSettings androidInitializationSettings;
  IOSInitializationSettings iosInitializationSettings;
  InitializationSettings initializationSettings;
  int pendingNotificationCount = 0;

  LocalNotification() {
    initLocalNotification();
  }

  int get totalNotifcation => pendingNotificationCount;

  Future<void> updateNotificationCount() async {
    List<PendingNotificationRequest> pendingNotifcationRequests =
        await flutterLocalNotificationsPlugin?.pendingNotificationRequests();
  }

  Future<int> getHighestNotificationId() async {
    List<PendingNotificationRequest> pendingNotifcationRequests =
        await flutterLocalNotificationsPlugin?.pendingNotificationRequests();
    int maxId = 0;
    pendingNotifcationRequests?.forEach((item) {
      if (item.id > maxId) maxId = item.id;
    });
    return maxId;
  }

  Future<int> getNotificationId(String title) async {
    List<PendingNotificationRequest> pendingNotifcationRequests =
        await flutterLocalNotificationsPlugin?.pendingNotificationRequests();
    final notification = pendingNotifcationRequests?.firstWhere(
      (item) => item.title == title,
      orElse: () => null,
    );
    if (notification != null) return notification.id;
    return null;
  }

  Future<void> cancelAllNotifications() async {
    await flutterLocalNotificationsPlugin?.cancelAll();
    await updateNotificationCount();
  }

  Future<void> cancelNotificationById(int notificationId) async {
    await flutterLocalNotificationsPlugin.cancel(notificationId);
  }

  Future<dynamic> onDidReceiveLocalNotification(
      int id, String title, String body, String payload) async {
    return ReceivedNotification(
        id: id, title: title, body: body, payload: payload);
  }

  Future<dynamic> onSelectNotification(String payload) async {
    if (payload != null) {
      debugPrint('notification payload: ' + payload);
    }
    // do something with notification based on paylod
  }

  Future<void> initLocalNotification() async {
    androidInitializationSettings = AndroidInitializationSettings('app_icon');
    iosInitializationSettings = IOSInitializationSettings(
        onDidReceiveLocalNotification: onDidReceiveLocalNotification);
    initializationSettings = InitializationSettings(
        android: androidInitializationSettings, iOS: iosInitializationSettings);
    await flutterLocalNotificationsPlugin?.initialize(initializationSettings,
        onSelectNotification: onSelectNotification);
    await updateNotificationCount();
  }

  Future<void> showNotification({
    @required String channelID,
    @required String channelName,
    @required String channelDesc,
    @required String notificationTitle,
    @required String notificationBody,
    String payload,
  }) async {
    AndroidNotificationDetails androidNotificationDetails =
        AndroidNotificationDetails(
      channelID,
      channelName,
      channelDesc,
      priority: Priority.high,
      importance: Importance.max,
      ticker: channelName,
    );
    IOSNotificationDetails iosNotificationDetails = IOSNotificationDetails();
    NotificationDetails notificationDetails = NotificationDetails(
        android: androidNotificationDetails, iOS: iosNotificationDetails);

    await flutterLocalNotificationsPlugin?.show(
        0, notificationTitle, notificationBody, notificationDetails,
        payload: 'item X');
  }

  Future<void> scheduledNotification(
      {@required String channelID,
      @required String channelName,
      @required String channelDesc,
      @required String notificationTitle,
      int notificationId,
      @required String notificationBody,
      @required DateTime notificationTime}) async {
    DateTime scheduledNotificationDateTime = notificationTime;

    AndroidNotificationDetails androidNotificationDetails =
        AndroidNotificationDetails(
      channelID,
      channelName,
      channelDesc,
      priority: Priority.high,
      importance: Importance.max,
      ticker: '$channelName',
    );

    IOSNotificationDetails iosNotificationDetails = IOSNotificationDetails();
    NotificationDetails notificationDetails = NotificationDetails(
        android: androidNotificationDetails, iOS: iosNotificationDetails);

    await flutterLocalNotificationsPlugin?.schedule(0, notificationTitle,
        notificationBody, scheduledNotificationDateTime, notificationDetails,
        payload: 'item X');
  }
}
