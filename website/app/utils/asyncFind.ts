export async function asyncFind<T>(
	array: T[],
	predicate: (value: T, index: number, array: T[]) => Promise<boolean>
) {
	for (const item of array) {
		if (await predicate(item, array.indexOf(item), array)) {
			return item
		}
	}
	return undefined
}
