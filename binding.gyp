{
	'targets': [
		{
			'target_name': 'addon',
			'sources': [
				'src/main.cc',
				'src/myobject.cc',
				'src/notification.cc'
			],

			'conditions': [
				['OS=="win"', {
					'libraries': [
						'-lnode.lib'
					]
				}, {
					'cflags': [
						'<!@(pkg-config libnotify --cflags)' #for libnotify
					],
					'libraries': [
						'<!@(pkg-config libnotify --libs)'
					]
				}]
			]
		}
		
	]
}
