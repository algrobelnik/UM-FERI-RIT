package dao

import InternalItem

interface InternalItemDao : DaoCrud<InternalItem> {
  fun getByInternalId(internalId: Int): InternalItem?
  fun getAllByDepartment(department: Int): List<InternalItem>
}